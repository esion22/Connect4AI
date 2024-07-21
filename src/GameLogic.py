import Board
import Disks
import random
import ctypes
import os

def playHuman (board: Board) -> int:
    print("In which column do you want to play?\n1 - 7")
    col = str(input())
    res: int
    if (col!="1" and col!="2" and col!="3" and col!="4" and col!="5" and col!="6" and col!="7"):
        print("invalid input!")
        res = 3
    else:
        col = int(col)  
        res = board.play(col-1, 0)

    correctInput: bool = False
    while (res == 3):
        correctInput = False
        while not correctInput:
            col = input("Choose another column: ")
            if (col!="1" and col!="2" and col!="3" and col!="4" and col!="5" and col!="6" and col!="7"):
                print("invalid input!")
            else:
                col = int(col)
                correctInput = True
        res = board.play(col-1, 0)
    print("\033c")
    print(board)
    return res

def playAI (board: Board) -> int:
    cBoard = (ctypes.c_int * 42)()
    for i in range(42):
        cBoard[i] = board.grid[i].value
    col: int = c.getPlay(cBoard)
    //print(col);
    res = board.play(col, 1)
    print(board)
    return res

if __name__ == "__main__":
    path = os.getcwd()
    c = ctypes.CDLL(os.path.join(path, 'AI.so'))

    print("Welcome to the connect4AI game, you are the human trying to overcome the AI.")
    print("You play with the 'O' and the AI plays with the 'X'.\n")

    board = Board.Board()

    playing: int = random.randint(0, 1)
    endGame: int
    if (playing == 0):
        print("The AI will begin.")
        print(board)
        endGame = playAI(board)
        playing = 1
    else:
        print("The human will start.")
        print(board)
        endGame = playHuman(board)
        playing = 0

    
    while (endGame == 2):
        if (board.isTie()):
                print("The human and the machine are equally strong.")
                endGame = 2
        elif playing == 0:
            print("AI is playing....")
            endGame = playAI(board)
            playing = 1
        else:
            endGame = playHuman(board)
            playing = 0



