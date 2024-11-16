#!python3
# -*- coding:utf-8 -*-

from dataclasses import dataclass
import hashlib

'''
UTXO 구조체
'''
@dataclass
class utxo:
    txid: str
    index: int
    amount: float

'''
Transaction 구조체(input은 1개이며, output은 여러 개일 수 있음)
'''
@dataclass
class transaction:
     txid: str
     input: str
     output_list: list

'''
Ouput 구조체
'''
@dataclass
class output:
    index: int
    amount: float
    address: str


class fullNode:
    def __init__(self, utxo_list: list[utxo], transaction_list: list[transaction]):
        self.utxo_set = [] # UTXO 집합
        self.transaction_set = [] # Block에 포함되기 위해 대기하고 있는 Transaction들의 집합

    def initialize(self, utxo_path, transaction_path):
        with open(utxo_path, 'r') as utxo_file:
            utxo = utxo_file.readline()
             
        # with open(transaction_path, 'r') as transaction_file:
        #     transaction = transaction_file.readline()

    '''
    Script 검증 함수 
    Return성공 시, True / 실패 시, False 반환
    '''
    def validate_script(self, locking_script, unlocking_script):
        op_set = set(['OP_DUP', 'OP_HASH', 'OP_EQUAL', 'OP_EQUALVERIFY', 'OP_CHECKSIG', 'OP_CHECKSIGVERIFY', 'OP_CHECKMULTISIG', 'OP_CHECKMULTISIGVERIFY', 'OP_CHECKFINALRESULT'])
        stack = [] # Stack based exceution 결과 판독을 위한 stack

        script_list = (unlocking_script + locking_script).split(' ')

        for i in range(len(script_list)):
            pointer = script_list[i]
            if pointer in op_set:
                if not self.operate(stack, pointer):
                    return False
            else:
                stack.append(pointer)

        if(len(stack) != 1):
            return False
        elif(len(stack) == 1 and stack[0] != 'True'):
            return False
        return True

    def hash(self, data, hash_type):
        if hash_type == 'sha256':
            return hashlib.sha256(data.encode()).hexdigest()
        elif hash_type == "hash160":
            return hashlib.new('ripemd160', hashlib.sha256(data.encode()).digest()).hexdigest()
        
    def snapshot_utxo(self): 
        return 
    
    def snapshot_transaction(self):
        return
    
    '''
    OP_DUP 연산자 함수 - Boolean으로 작업 성공/실패 여부 반환
    '''
    def op_dup(self, stack: list):
        if len(stack) < 1:
            return False
        top = stack.pop()
        stack.append(top)
        stack.append(top)
        return True

    def op_hash160(self, stack: list):
        if len(stack) < 1:
            return False
        top = stack.pop()
        
        return True
    
    def op_equal(self, stack: list):
        if len(stack) < 2:
            return False
        top1 = stack.pop()
        top2 = stack.pop()
        stack.append(top1 == top2)
        return True
    
    def op_checksig(self, stack: list):
        if len(stack) < 2:
            return False
        pubkey = stack.pop()
        signature = stack.pop()
        return True

    def op_checksigverify(self, stack: list):
        return True
    
    def op_checkmultisig(self, stack: list):
        return True
    
    def op_checkfinalresult(self, stack: list):
        return True