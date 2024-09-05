from enum import Enum

class Disk(Enum):
    YELLOW = 1
    RED = 0
    EMPTY = -1
    WINRED = 2
    WINYELLOW = 3

    def __str__(self) -> str:
        if (self == Disk.EMPTY):
            return " "
        elif (self == Disk.YELLOW):
            return "\033[33mX\033[0m"
        elif (self == Disk.RED):
            return "\033[31mO\033[0m"
        elif (self == Disk.WINRED):
            return "\033[32mO\033[0m"
        elif (self == Disk.WINYELLOW):
            return "\033[32mX\033[0m"