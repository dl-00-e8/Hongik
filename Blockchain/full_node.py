#!python3
# -*- coding:utf-8 -*-

import json
from dataclasses import dataclass
import hashlib
import ecdsa

'''
UTXO 구조체
'''
@dataclass
class utxo:
    txid: str
    outputIdx: int
    amount: float
    lockingScript: str

'''
Transaction 구조체(input은 1개이며, output은 여러 개일 수 있음)
'''
@dataclass
class transaction:
     txid: str
     input: list
     unlockingScript: list
     output_list: list

'''
Ouput 구조체
'''
@dataclass
class output:
    outputIdx: int
    amount: float
    lockingScript: str


class fullNode:
    def __init__(self, utxo_path, transaction_path):
        self.utxo_set = [] # UTXO 집합
        self.transaction_set = [] # Block에 포함되기 위해 대기하고 있는 Transaction들의 집합
        self.processed_transaction_list = [] # 현재까지 처리된 트랜잭션 정보 담음
        self.stack = []

        self.initialize(utxo_path=utxo_path, transaction_path=transaction_path)
        self.execute()

    def initialize(self, utxo_path: str, transaction_path: str):
        # 트랜잭션 파일 먼저 읽기
        with open(transaction_path, 'r') as transaction_file:
            transaction_list = json.load(transaction_file)
            
            # 필요한 UTXO 집합 구성
            required_utxos = set()
            for data in transaction_list:
                for inp in data['input']:
                    utxo_data = inp['utxo']
                    required_utxos.add((utxo_data['txid'], utxo_data['outputIdx']))
                    
            # UTXO 파일 읽기
            with open(utxo_path, 'r') as utxo_file:
                utxo_list = json.load(utxo_file)
                for data in utxo_list:
                    self.utxo_set.append(utxo(**data))
                    if (data['txid'], data['outputIdx']) in required_utxos:
                        required_utxos.remove((data['txid'], data['outputIdx']))
            
            # 누락된 UTXO 추가
            for txid, outputIdx in required_utxos:
                for tx in transaction_list:
                    for inp in tx['input']:
                        if inp['utxo']['txid'] == txid and inp['utxo']['outputIdx'] == outputIdx:
                            self.utxo_set.append(utxo(**inp['utxo']))
                            
            # 트랜잭션 객체 생성
            for data in transaction_list:
                txid = data['txid']
                input_list = [utxo(**inp['utxo']) for inp in data['input']]
                unlocking_script_list = [inp['unlockingScript'] for inp in data['input']]
                output_list = [output(**out) for out in data['output']]
                self.transaction_set.append(transaction(txid=txid, input=input_list, unlockingScript=unlocking_script_list, output_list=output_list))

    def execute(self):
        '''
        EE 실행, 각 트랜잭션 처리 후 결과 출력
        transaction: txid
            input: txid, outputIdx, amount, lockingScript
            output0: outputIdx, amount, lockingScript
            output1: outputIdx, amount, lockingScript
            validity check: passed (or failed at xxx, xxx는 명령어 위치)
        '''
        for transaction in self.transaction_set:
            print(f"transaction: {transaction.txid}")
            
            # 입력 출력 정보 출력
            for input_utxo in transaction.input:
                print(f"    input: txid={input_utxo.txid}, outputIdx={input_utxo.outputIdx}, amount={input_utxo.amount}, lockingScript={input_utxo.lockingScript}")
            for output in transaction.output_list:
                print(f"    output{output.outputIdx}: txid={transaction.txid}, outputIdx={output.outputIdx}, amount={output.amount}, lockingScript={output.lockingScript}")

            # 각 입력에 대해 스크립트 검증
            for i in range(len(transaction.input)):
                input_utxo = transaction.input[i]
                unlocking_script = transaction.unlockingScript[i]
                
                # 트랜잭션 데이터를 반복문에서 꺼내와서 활용
                transaction_data = transaction.txid.encode()
                
                # 스크립트 검증
                result, failed_index = self.validate_script(input_utxo.lockingScript, unlocking_script, transaction_data)
                if not result:
                    script_list = (unlocking_script + input_utxo.lockingScript).split(' ')
                    failed_command = script_list[failed_index]
                    print(f"    validity check: failed at {failed_command}")
                    break
            else:
                print("    validity check: passed")
                
                # 검증 성공한 경우 UTXO 업데이트
                for input_utxo in transaction.input:
                    self.utxo_set.remove(input_utxo)
                for output in transaction.output_list:
                    self.utxo_set.append(utxo(
                        txid=transaction.txid,
                        outputIdx=output.outputIdx,
                        amount=output.amount,
                        lockingScript=output.lockingScript
                    ))


    def validate_script(self, locking_script, unlocking_script, transaction_data: bytes):
        '''
        Script 검증 함수 
        Return성공 시, True / 실패 시, False 반환
        '''
        op_set = set(['OP_DUP', 'OP_HASH160', 'OP_EQUAL', 'OP_EQUALVERIFY', 'OP_CHECKSIG', 'OP_CHECKSIGVERIFY', 'OP_CHECKMULTISIG', 'OP_CHECKMULTISIGVERIFY', 'OP_CHECKFINALRESULT'])
        self.stack = [] # Stack based exceution 결과 판독을 위한 stack

        script_list = (unlocking_script + locking_script).split(' ')
        i = 0
        while i < len(script_list):
            pointer = script_list[i]
            if pointer in op_set:
                # 각 연산자에 맞는 함수 호출
                if pointer == 'OP_DUP':
                    if not self.op_dup(self.stack):
                        return False, i
                elif pointer == 'OP_HASH160':
                    if not self.op_hash160(self.stack):
                        return False, i
                elif pointer == 'OP_EQUAL':
                    if not self.op_equal(self.stack):
                        return False, i
                elif pointer == 'OP_EQUALVERIFY':
                    if not self.op_equalverify(self.stack):
                        return False, i
                elif pointer == 'OP_CHECKSIG':
                    if not self.op_checksig(self.stack, transaction_data):
                        return False, i
                elif pointer == 'OP_CHECKSIGVERIFY':
                    if not self.op_checksigverify(self.stack, transaction_data):
                        return False, i
                elif pointer == 'OP_CHECKMULTISIG':
                    if not self.op_checkmultisig(self.stack):
                        return False, i
                elif pointer == 'OP_CHECKFINALRESULT':
                    if not self.op_checkfinalresult(self.stack):
                        return False, i
            elif pointer == 'IF':
                if len(self.stack) < 1:
                    return False, i
                condition = self.stack.pop()
                if condition != 'TRUE':
                    # IF 조건이 거짓이면 ELSE나 ENDIF까지 건너뛰기
                    while i < len(script_list) and script_list[i] not in ['ELSE', 'ENDIF']:
                        i += 1
                    if i < len(script_list) and script_list[i] == 'ELSE':
                        i += 1
            elif pointer == 'ELSE':
                # ENDIF까지 건너뛰기
                while i < len(script_list) and script_list[i] != 'ENDIF':
                    i += 1
            elif pointer == 'ENDIF':
                pass
            else:
                self.stack.append(pointer)
            i += 1

        if len(self.stack) != 1:
            return False, i
        elif len(self.stack) == 1 and self.stack[0] != 'TRUE':
            return False, i
        return True, i
    
    def op_dup(self, stack: list):
        '''
        OP_DUP 연산자 함수 - Boolean으로 작업 성공/실패 여부 반환
        '''
        if len(stack) < 1:
            return False
        top = stack.pop()
        stack.append(top)
        stack.append(top)
        return True

    def op_hash160(self, stack: list):
        '''
        OP_HASH160 연산자 함수 - Boolean으로 작업 성공/실패 여부 반환
        SHA256으로 암호화 이후, RIPEMD160으로 암호화한 값을 stack에 삽입
        '''
        if len(stack) < 1:
            return False
        top = stack.pop()
        
        # SHA256 암호화
        sha256_hashed = hashlib.sha256(top.encode()).digest()
        # RIPEMD160 암호화
        ripemd160_hashed = hashlib.new('ripemd160', sha256_hashed).hexdigest()
        
        stack.append(ripemd160_hashed)
        return True
    
    def op_equal(self, stack: list):
        '''
        OP_EQUAL 연산자 함수 - Boolean으로 작업 성공/실패 여부 반환
        stack의 top 두 원소를 pop하여 비교한 결과 같으면 TRUE, 아니면 FALSE를 stack에 push
        '''
        if len(stack) < 2:
            return False
        top1 = stack.pop()
        top2 = stack.pop()
        if top1 == top2:
            stack.append('TRUE')
        else:
            stack.append('FALSE')
        return True
    
    def op_equalverify(self, stack: list):
        '''
        OP_EQUALVERIFY 연산자 함수 - Boolean으로 작업 성공/실패 여부 반환
        stack의 top 두 원소를 pop하여 비교한 결과 같으면 True 반환, 아니면 False 반환
        '''
        if len(stack) < 2:
            return False
        top1 = stack.pop()
        top2 = stack.pop()
        if top1 == top2:
            return True
        return False

    def op_checksig(self, stack: list, transaction_data: bytes):
        '''
        OP_CHECKSIG 연산자 함수 - Boolean으로 작업 성공/실패 여부 반환
        stack의 top 두 원소를 pop하여 top 원소(pubKey)를 이용하여 signature를 검증
        검증 결과 서명이 유효하면 stack에 TRUE를, 아니면 FALSE를 push
        '''
        if len(stack) < 2:
            return False
        pubkey = stack.pop()
        signature = stack.pop()
        
        try:
            # secp256k1 곡선을 사용하는 ECDSA 검증
            vk = ecdsa.VerifyingKey.from_string(bytes.fromhex(pubkey), curve=ecdsa.SECP256k1)
            is_valid = vk.verify(bytes.fromhex(signature), transaction_data, hashfunc=hashlib.sha256)
            if is_valid:
                stack.append("TRUE")
            else:
                stack.append("FALSE")
            return True
        except:
            stack.append("FALSE")
            return True

    def op_checksigverify(self, stack: list, transaction_data: bytes):
        '''
        OP_CHECKSIGVERIFY 연산자 함수 - Boolean으로 작업 성공/실패 여부 반환
        CHECKSIG와 같으나 검증 결과 서명이 유효하면 계속 진행하고, 그렇지 않으면 중단
        '''
        if len(stack) < 2:
            return False
        pubkey = stack.pop()
        signature = stack.pop()
        
        try:
            # secp256k1 곡선을 사용하는 ECDSA 검증
            vk = ecdsa.VerifyingKey.from_string(bytes.fromhex(pubkey), curve=ecdsa.SECP256k1)
            is_valid = vk.verify(bytes.fromhex(signature), transaction_data, hashfunc=hashlib.sha256)
            if is_valid:
                return True
            return False
        except:
            return False
    
    def op_checkmultisig(self, stack: list):
        '''
        OP_CHECKMULTISIG 연산자 함수 - Boolean으로 작업 성공/실패 여부 반환
        m-of-n 다중 서명 검증을 수행
        '''
        if len(stack) < 1:
            return False
            
        n = int(stack.pop())  # 공개키 개수
        if len(stack) < n + 1:
            return False
            
        pubkeys = []
        for _ in range(n):
            pubkeys.append(stack.pop())
            
        m = int(stack.pop())  # 필요한 서명 개수
        if len(stack) < m + 1:
            return False
            
        signatures = []
        for _ in range(m):
            signatures.append(stack.pop())
            
        # 더미 값 제거 (Bitcoin의 버그 호환성)
        stack.pop()
        
        # 트랜잭션 데이터 해시 생성
        tx_hash = hashlib.sha256(str(self.transaction_set).encode()).digest()
        
        # 각 서명에 대해 검증 수행
        try:
            valid_sigs = 0
            for signature in signatures:
                for pubkey in pubkeys:
                    try:
                        vk = ecdsa.VerifyingKey.from_string(bytes.fromhex(pubkey), curve=ecdsa.SECP256k1)
                        if vk.verify(bytes.fromhex(signature), tx_hash):
                            valid_sigs += 1
                            break
                    except:
                        continue
                        
            if valid_sigs == m:
                stack.append("TRUE")
                return True
            else:
                stack.append("FALSE")
                return True
                
        except:
            stack.append("FALSE")
            return True
        
    def op_checkmultisigverify(self, stack: list):
        if len(stack) < 1:
            return False
            
        n = int(stack.pop())  # 공개키 개수
        if len(stack) < n + 1:
            return False
            
        pubkeys = []
        for _ in range(n):
            pubkeys.append(stack.pop())
            
        m = int(stack.pop())  # 필요한 서명 개수
        if len(stack) < m + 1:
            return False
            
        signatures = []
        for _ in range(m):
            signatures.append(stack.pop())
            
        # 더미 값 제거 (Bitcoin의 버그 호환성)
        stack.pop()
        
        # 트랜잭션 데이터 해시 생성
        tx_hash = hashlib.sha256(str(self.transaction_set).encode()).digest()
        
        # 각 서명에 대해 검증 수행
        try:
            valid_sigs = 0
            for signature in signatures:
                for pubkey in pubkeys:
                    try:
                        vk = ecdsa.VerifyingKey.from_string(bytes.fromhex(pubkey), curve=ecdsa.SECP256k1)
                        if vk.verify(bytes.fromhex(signature), tx_hash):
                            valid_sigs += 1
                            break
                    except:
                        continue
                        
            # M개의 유효한 서명이 있는 경우에만 True 반환
            return valid_sigs == m
                
        except:
            return False
    
    def op_checkfinalresult(self, stack: list):
        '''
        스크립트 실행의 최종 결과를 검증하는 함수
        스택에 원소가 하나이고 그 값이 TRUE인 경우에만 유효(True)를 반환
        그 외의 모든 경우에는 유효하지 않음(False)을 반환
        '''
        if len(stack) == 1 and stack[-1] == "TRUE":
            return True
        return False
    
    def snapshot_utxo(self): 
        '''
        쿼리 프로세스를 통해, 현재 시점의 UTXO 집합의 내용을 받아 다음과 같이 출력
        utxo0: txid0, output index0, amonut0, locking script0
        utxo1: txid1, output index1, amonut1, locking script1
        '''
        result = []
        for i, utxo in enumerate(self.utxo_set):
            utxo_str = f"utxo{i}: {utxo.txid}, {utxo.outputIdx}, {utxo.amount}, {utxo.lockingScript}"
            result.append(utxo_str)
        return result
    
    def snapshot_transaction(self):
        '''
        쿼리 프로세스를 통해 현재까지 처리된 트랜잭션의 txid 및 유효성(요약) 정보 반환
        transaction: txid, validity check: passed / failed
        '''
        result = []
        for tx in self.processed_transaction_list:
            tx_str = f"transaction: {tx.txid}, validity check: {'passed' if tx.valid else 'failed'}"
            result.append(tx_str)
        return result
    
    
if __name__ == "__main__":
    node = fullNode('./utxoes.json', './transaction.json')