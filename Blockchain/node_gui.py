#!python3
# -*- coding:utf-8 -*-

import tkinter as tk
from tkinter import ttk
from full_node import fullNode

class NodeGUI:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("블록체인 실행 엔진")
        self.root.geometry('400x600+100+100')
        self.root.resizable(True, True)
        self.node = fullNode()

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