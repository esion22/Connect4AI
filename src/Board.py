from Disks import *

class Board():

    def __init__(self) -> None:
        self.grid = []
        for i in range(49):
            self.grid.append(Disk.EMPTY)
    
    def __str__(self) -> str:
        string: str = "\n";
        for i in range(7):
            for j in range (7):
                string += "|"
                string += str(self.grid[i*7 + j])
                string += "|"
            string += "\n"
        string += " 1  2  3  4  5  6  7 \n"
        string += "\n"
        return string
    
    def play (self, col: int, which: int) -> None:
        if (self.grid[col] != Disk.EMPTY):
            print("Unable to play here!")
            return

        i: int = 0
        while (self.grid[i*7 + col] == Disk.EMPTY and i != 6):
            i += 1
        
        if (self.grid[i*7 + col] != Disk.EMPTY):
            i -= 1
        
        if (which == 0):
            self.grid[i*7 + col] = Disk.RED
        else:
            self.grid[i*7 + col] = Disk.YELLOW

    def isWinner(self) -> int:
        # the result is 0 if the human wins, 1 if the AI wins, 2 if nobody wins
        pass

board = Board()
board.play(1, 0)
board.play(2, 1)
board.play(3, 0)
board.play(1, 1)
board.play(1, 0)
board.play(1, 1)
board.play(1, 0)
board.play(1, 1)
board.play(1, 0)
board.play(1, 1)
print(board)