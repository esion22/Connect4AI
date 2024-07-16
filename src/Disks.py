from enum import Enum, auto

class Disk(Enum):
    YELLOW = 1
    RED = 0
    EMPTY = -1

    def __str__(self) -> str:
        if (self == Disk.EMPTY):
            return " "
        elif (self == Disk.YELLOW):
            return "\033[33mX\033[0m"
        elif (self == Disk.RED):
            return "\033[31mO\033[0m"