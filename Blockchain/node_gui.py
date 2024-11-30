#!python3
# -*- coding:utf-8 -*-

from tkinter import *
from tkinter import ttk
from full_node import fullNode

class NodeGUI:
    def __init__(self):
        self.root = Tk()
        self.root.title("블록체인 실행 엔진")
        self.root.geometry('400x600+100+100')
        self.root.resizable(True, True)
        self.node = fullNode('./utxo.json', './transaction.json')

        # Execution Engine 실행 버튼
        self.execution_engine_button = Button(self.root, text = "Execution Engine 실행", font=('Pretendard', 15)) #, command = decode)
        self.execution_engine_button.grid(row = 0, column = 0)

        # 각 트랜잭션 처리 후 결과 출력
        self.result_text = Text(self.root, width=50, height=10)
        self.result_text.configure(font=('Pretendard', 15))
        self.result_text.grid(row=1, column=0, padx=25, pady=10)
        self.result_text.insert(END, "트랜잭션 처리 결과가 여기에 표시됩니다.\n")

        # Query Process 확인 버튼
        self.query_process_button = Button(self.root, text = "Query Process 확인", font=('Pretendard', 15)) #, command = decode)
        self.query_process_button.grid(row = 2, column = 0)

        # UTXO 상태 테이블
        self.tx_text = Label(self.root, text = "UTXO 상태 테이블", font = ('Pretendard', 15, 'bold'))
        self.tx_text.grid(row = 3, column = 0, padx = 10)
        self.utxo_table = ttk.Treeview(self.root, columns=("txid", "index", "amount"), show='headings')
        self.utxo_table.heading("txid", text="Transaction ID")
        self.utxo_table.heading("index", text="Index")
        self.utxo_table.heading("amount", text="Amount")
        self.utxo_table.grid(row=4, column=0, pady=10)

        # 트랜잭션 상태 테이블
        self.tx_text = Label(self.root, text = "트랜잭션 상태 테이블", font = ('Pretendard', 15, 'bold'))
        self.tx_text.grid(row = 5, column = 0, padx = 10)
        self.tx_table = ttk.Treeview(self.root, columns=("txid", "status"), show='headings')
        self.tx_table.heading("txid", text="Transaction ID")
        self.tx_table.heading("status", text="Status")
        self.tx_table.grid(row=6, column=0, pady=10)
        
    def update_transaction_table(self):
        """트랜잭션 상태 테이블 업데이트"""
        for item in self.tx_table.get_children():
            self.tx_table.delete(item)
        
        for txid, status in self.node.tx_status.items():
            self.tx_table.insert("", "end", values=(txid, status))

    def update_utxo_table(self):
        """UTXO 상태 테이블 업데이트"""
        for item in self.utxo_table.get_children():
            self.utxo_table.delete(item)
        
        utxo_status = self.node.snapshot_utxo()
        for utxo in utxo_status:
            self.utxo_table.insert("", "end", values=(utxo['txid'], utxo['index'], utxo['amount']))


    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    NodeGUI().run()

'''
intro = Label(gui, text = "변환 값 입력", font = ('현대하모니 L', 14, 'bold'))
intro.grid(row = 0, column = 0, padx = 10)

line = Text(gui, width = 50, height = 10)
line.configure(font = ('현대하모니 L', 10))
line.gird(row = 1, column = 0, padx = 23, pady = 10)

conversion = Button(gui, text = "변환", command = decode)
conversion.grid(row = 2, column = 0)

cpIntro = Label(gui, text = "CP959 변환", font = ('현대하모니 L', 12))
cpIntro.grid(row = 3, column = 0)

cpOutput = Text(gui, width = 50, height = 8)
cpOutput.configure(font = ('현대하모니 L', 10))
cpOutput.grid(row = 4, column = 0, padx = 23, pady = 10)

utfIntro = Label(gui, text = "UTF-8 변환", font = ('현대하모니 L', 12))
utfIntro.grid(row = 5, column = 0)

utfOutput = Text(gui, width = 50, height = 8)
utfOutput.configure(font = ('현대하모니 L', 10))
utfOutput.grid(row = 6, column = 0, padx = 23, pady = 10)
'''