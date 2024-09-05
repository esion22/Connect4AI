import tkinter as tk
from tkinter import messagebox
import Board
import random
import ctypes
import os
import threading as th

class GUI:
    buttons = list()
    path = os.getcwd()
    c = ctypes.CDLL(os.path.join(path, 'AI.so'))

    def __init__(self, board: Board) -> None:
        self.root = tk.Tk()
        self.root.geometry("700x600")
        self.root.title("Connect 4 AI")
        self.root.resizable(False, False)
        self.root.configure(background="blue")

        tk.messagebox.showinfo("connect4 AI", "You are about to play against an AI.\n"
                                              "You are assigned the RED color, the AI will play as YELLOW.\n"
                                              "To play click on any square of the corresponding column you want to play in.")

        def onClick(x: int, board: Board):
            self.playHuman(board, x)

        for i in range(6):
            for j in range(7):
                button = tk.Button(width=8, height=5, background="dark blue", highlightbackground="black")
                button.grid(row=i, column=j, sticky="NSWE")
                self.buttons.append(button)

        for i in range(6):
            self.buttons.__getitem__(7*i).configure(command = lambda: onClick(0, board))
            self.buttons.__getitem__(7*i+1).configure(command=lambda: onClick(1, board))
            self.buttons.__getitem__(7*i+2).configure(command=lambda: onClick(2, board))
            self.buttons.__getitem__(7*i+3).configure(command=lambda: onClick(3, board))
            self.buttons.__getitem__(7*i+4).configure(command=lambda: onClick(4, board))
            self.buttons.__getitem__(7*i+5).configure(command=lambda: onClick(5, board))
            self.buttons.__getitem__(7*i+6).configure(command=lambda: onClick(6, board))

        playing: int = random.randint(0, 1)

        if (playing == 0):
            t = th.Thread(self.playAI(board))
            t.start()
            tk.messagebox.showinfo("connect4 AI", "the AI will start playing")
            t.join()
        else:
            tk.messagebox.showinfo("connect4 AI", "the human will start playing")

        self.root.mainloop()

    def playHuman(self, board: Board, col: int):
        res = board.play(col, 0, self)
        if (res == 0 or res == 3):
            #human won or tie
            self.endGame(res)
        else:
            self.playAI(board)


    def playAI(self, board: Board):
        cBoard = (ctypes.c_int * 42)()
        for i in range(42):
            cBoard[i] = board.grid[i].value
        col: int = self.c.getPlay(cBoard)
        # print(col);
        res = board.play(col, 1, self)
        if (res == 1 or res == 3):
            #AI won or tie
            self.endGame(res)

    def endGame(self, which: int):
        for i in range(42):
            self.buttons.__getitem__(i).configure(state=tk.DISABLED)

        if (which == 0):
            tk.messagebox.showinfo("connect4 AI", "the human rules over the machine")
        elif (which == 1):
            tk.messagebox.showinfo("connect4 AI", "the machine has overcome humans")
        else:
            tk.messagebox.showinfo("connect4 AI", "the machine and the human are equally strong")
        self.root.destroy()


if __name__ == "__main__":
    board = Board.Board()
    gui = GUI(board)