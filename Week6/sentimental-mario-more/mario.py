# TODO
from cs50 import get_int

height = -1
while height <= 0 or height > 8:
    height = get_int("Height: ")

for y in range(1, height + 1):
    for x in range(1, height + 1):
        if x > height - y:
            print("#", end="")
        else:
            print(" ", end="")
        if x == height:
            print(" ", "#" * y, end="")
    print("")
