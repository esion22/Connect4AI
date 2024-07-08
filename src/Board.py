from Disks import *

# human is Red (0) AI is Yellow (1)

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
        
        winner: int = self.isWinner()
        if (winner == 0):
            print(self)
            print("The human rules over the machine")
        elif (winner == 1):
            print(self)
            print("The Machine has overcome humans...")

        

    def isWinner(self) -> int:
        # the result is 0 if the human wins, 1 if the AI wins, 2 if nobody wins
        value: Disk = None
        for i in range(7):
            # only check up, right, up-right, up-left
            for j in range(7):
                value = self.grid[i*7 + j]
                if value != Disk.EMPTY:
                    if i>=3:
                        #check up
                        if (self.grid[(i-1)*7 + j] == value and self.grid[(i-2)*7 + j] == value and self.grid[(i-3)*7 + j] == value):
                            if value == Disk.RED:
                                return 0
                            elif value == Disk.YELLOW:
                                return 1
                    if j<=3:
                        #check right
                        if (self.grid[i*7 + j + 1] == value and self.grid[i*7 + j + 2] == value and self.grid[i*7 + j + 3] == value):
                            if value == Disk.RED:
                                return 0
                            elif value == Disk.YELLOW:
                                return 1
                    if i>=3 and j<=3:
                        #check up-right
                        if (self.grid[(i-1)*7 + j + 1] == value and self.grid[(i-2)*7 + j + 2] == value and self.grid[(i-3)*7 + j + 3] == value):
                            if value == Disk.RED:
                                return 0
                            elif value == Disk.YELLOW:
                                return 1
                    if i>=3 and j>=3:
                        #check up-left
                        if (self.grid[(i-1)*7 + j - 1] == value and self.grid[(i-2)*7 + j - 2] == value and self.grid[(i-3)*7 + j - 3] == value):
                            if value == Disk.RED:
                                return 0
                            elif value == Disk.YELLOW:
                                return 1
        return 2
                    

board = Board()

