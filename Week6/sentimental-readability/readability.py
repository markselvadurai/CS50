# TODO
from cs50 import get_string

text = get_string("Text: ")

letters = 0
words = 0
L = 0
punct = ["!", ".", "?"]
sentences = 0

for character in text:
    if character.isalpha():
        letters += 1

for char in text:
    if words == 0:
        words = 1
    if char == " ":
        words += 1

for charac in text:
    if charac in punct:
        sentences += 1

L = (letters / words) * 100
S = (sentences / words) * 100

rlevel = round(((0.0588 * L) - (0.296 * S)) - 15.8)

if rlevel >= 16:
    print("Grade 16+")
elif rlevel < 1:
    print("Before Grade 1")
else:
    print(f"Grade {rlevel}")
