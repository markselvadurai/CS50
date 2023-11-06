# TODO
from cs50 import get_int
from cs50 import get_string

while True:
    cardnum = get_string("Number: ")
    if cardnum.isdigit():
        break


validcard = 0
validcardstr = ""
validcard2 = 0
valid = False
off = "0"

if len(cardnum) % 2 == 0:
    for i in range(0, len(cardnum), 2):
        validcardstr += str(int(cardnum[i]) * 2)
        if i < len(cardnum) - 1:
            validcard2 += int(cardnum[i + 1])
else:
    off += cardnum
    for i in range(0, len(off), 2):
        validcardstr += str(int(off[i]) * 2)
        if i < len(off) - 1:
            validcard2 += int(off[i + 1])
for c in validcardstr:
    validcard += int(c)
validcard += validcard2
validcardstr = str(validcard)
if validcardstr[len(validcardstr) - 1] == "0":
    valid = True
amex = ["34", "37"]
mc = ["51", "52", "53", "54", "55"]
visa = ["4"]

if valid:
    if len(cardnum) == 15:
        if cardnum[0:2] in amex:
            print("AMEX\n")
        else:
            print("INVALID\n")
    elif len(cardnum) == 16:
        print(cardnum[0])
        if cardnum[0:2] in mc:
            print("MASTERCARD\n")
        elif cardnum[0] in visa:
            print("VISA\n")
        else:
            print("INVALID\n")
    elif len(cardnum) == 13:
        if cardnum[0] in visa:
            print("VISA\n")
        else:
            print("INVALID\n")
    else:
        print("INVALID\n")
else:
    print("INVALID\n")
