from enum import Enum, auto

class Disk(Enum):
    YELLOW = auto()
    RED = auto()
    EMPTY = auto()

    def __str__(self) -> str:
        if (self == Disk.EMPTY):
            return " "
        elif (self == Disk.YELLOW):
            return "X"
        elif (self == Disk.RED):
            return "O"