from enum import Enum, auto

class Disk(Enum):
    YELLOW = 1
    RED = 0
    EMPTY = -1

    def __str__(self) -> str:
        if (self == Disk.EMPTY):
            return " "
        elif (self == Disk.YELLOW):
            return "X"
        elif (self == Disk.RED):
            return "O"