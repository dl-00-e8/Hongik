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
        self.utxo_set = []

    def initialize(self, utxo_path, transaction_path):
        with open(utxo_path, 'r') as utxo_file:
            utxo = utxo_file.readline()
             
        # with open(transaction_path, 'r') as transaction_file:
        #     transaction = transaction_file.readline()

    def validate_script(self, locking_script, unlocking_script):
        stack = [] # Stack based exceution 결과 판독을 위한 stack
        pass

    def hash(self, data, hash_type):
        if hash_type == 'sha256':
            return hashlib.sha256(data.encode()).hexdigest()
        elif hash_type == "hash160":
            return hashlib.new('ripemd160', hashlib.sha256(data.encode()).digest()).hexdigest()
        
    def snapshot_utxo(self): 
        return 
    
    def snapshot_transaction(self):
        return