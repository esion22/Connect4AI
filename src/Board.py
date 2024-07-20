from Disks import *
import ctypes

# human is Red (0) AI is Yellow (1)

class Board():

    def __init__(self) -> None:
        self.grid = []
        for i in range(42):
            self.grid.append(Disk.EMPTY)
    
    def __str__(self) -> str:
        string: str = "\n";
        for i in range(6):
            for j in range (7):
                string += "\033[34m|\033[0m"
                string += str(self.grid[i*7 + j])
                string += "\033[34m|\033[0m"
            string += "\n"
        string += " 1  2  3  4  5  6  7 \n"
        string += "\n"
        return string
    
    def isTie (self) -> bool:
        isTie: bool = True
        for i in range(7):
            if (self.grid[i] == Disk.EMPTY):
                isTie = False
                break
        
        return isTie


    def play (self, col: int, which: int) -> int:
        if (self.grid[col] != Disk.EMPTY):
            print("Unable to play here!")
            return 3

        i: int = 0
        while (self.grid[i*7 + col] == Disk.EMPTY and i != 5):
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
        return winner

        

    def isWinner(self) -> int:
        # the result is 0 if the human wins, 1 if the AI wins, 2 if nobody wins
        value: Disk = None
        for i in range(6):
            # only check up, right, up-right, up-left
            for j in range(7):
                value = self.grid[i*7 + j]
                if value != Disk.EMPTY:
                    if i>=3:
                        #check up
                        if (self.grid[(i-1)*7 + j] == value and self.grid[(i-2)*7 + j] == value and self.grid[(i-3)*7 + j] == value):
                            if value == Disk.RED:
                                self.grid[i*7 + j] = Disk.WINRED
                                self.grid[(i-1)*7 + j] = Disk.WINRED
                                self.grid[(i-2)*7 + j] = Disk.WINRED
                                self.grid[(i-3)*7 + j] = Disk.WINRED
                                return 0
                            elif value == Disk.YELLOW:
                                self.grid[i*7 + j] = Disk.WINYELLOW
                                self.grid[(i-1)*7 + j] = Disk.WINYELLOW
                                self.grid[(i-2)*7 + j] = Disk.WINYELLOW
                                self.grid[(i-3)*7 + j] = Disk.WINYELLOW
                                return 1
                    if j<=3:
                        #check right
                        if (self.grid[i*7 + j + 1] == value and self.grid[i*7 + j + 2] == value and self.grid[i*7 + j + 3] == value):
                            if value == Disk.RED:
                                self.grid[i*7 + j] = Disk.WINRED
                                self.grid[i*7 + j + 1] = Disk.WINRED
                                self.grid[i*7 + j + 2] = Disk.WINRED
                                self.grid[i*7 + j + 3] = Disk.WINRED
                                return 0
                            elif value == Disk.YELLOW:
                                self.grid[i*7 + j] = Disk.WINYELLOW
                                self.grid[i*7 + j + 1] = Disk.WINYELLOW
                                self.grid[i*7 + j + 2] = Disk.WINYELLOW
                                self.grid[i*7 + j + 3] = Disk.WINYELLOW
                                return 1
                    if i>=3 and j<=3:
                        #check up-right
                        if (self.grid[(i-1)*7 + j + 1] == value and self.grid[(i-2)*7 + j + 2] == value and self.grid[(i-3)*7 + j + 3] == value):
                            if value == Disk.RED:
                                self.grid[i*7 + j] = Disk.WINRED
                                self.grid[(i-1)*7 + j + 1] = Disk.WINRED
                                self.grid[(i-2)*7 + j + 2] = Disk.WINRED
                                self.grid[(i-3)*7 + j + 3] = Disk.WINRED
                                return 0
                            elif value == Disk.YELLOW:
                                self.grid[i*7 + j] = Disk.WINYELLOW
                                self.grid[(i-1)*7 + j + 1] = Disk.WINYELLOW
                                self.grid[(i-2)*7 + j + 2] = Disk.WINYELLOW
                                self.grid[(i-3)*7 + j + 3] = Disk.WINYELLOW
                                return 1
                    if i>=3 and j>=3:
                        #check up-left
                        if (self.grid[(i-1)*7 + j - 1] == value and self.grid[(i-2)*7 + j - 2] == value and self.grid[(i-3)*7 + j - 3] == value):
                            if value == Disk.RED:
                                self.grid[i*7 + j] = Disk.WINRED
                                self.grid[(i-1)*7 + j - 1] = Disk.WINRED
                                self.grid[(i-2)*7 + j - 2] = Disk.WINRED
                                self.grid[(i-3)*7 + j - 3] = Disk.WINRED
                                return 0
                            elif value == Disk.YELLOW:
                                self.grid[i*7 + j] = Disk.WINYELLOW
                                self.grid[(i-1)*7 + j - 1] = Disk.WINYELLOW
                                self.grid[(i-2)*7 + j - 2] = Disk.WINYELLOW
                                self.grid[(i-3)*7 + j - 3] = Disk.WINYELLOW
                                return 1
        return 2
