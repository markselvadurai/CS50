import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE SEQUENCE")

    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1], "r") as db:
        reader = csv.reader(db)
        next(reader)
        for item in reader:
            database.append(item)

    # TODO: Read DNA sequence file into a variable
    sequence = []
    with open(sys.argv[2], "r") as seq:
        seqread = csv.reader(seq)
        for it in seqread:
            sequence.append(it)

    # TODO: Find longest match of each STR in DNA sequence
    LAGATC = longest_match(sequence[0][0], "AGATC")
    LTTTTTTCT = longest_match(sequence[0][0], "TTTTTTCT")
    LTCTAG = longest_match(sequence[0][0], "TCTAG")
    LAATG = longest_match(sequence[0][0], "AATG")
    LGATA = longest_match(sequence[0][0], "GATA")
    LTATC = longest_match(sequence[0][0], "TATC")
    LGAAA = longest_match(sequence[0][0], "GAAA")
    LTCTG = longest_match(sequence[0][0], "TCTG")

    longestlarge = [LAGATC, LTTTTTTCT, LAATG, LTCTAG, LGATA, LTATC, LGAAA, LTCTG]

    longestsmall = [LAGATC, LAATG, LTATC]
    # TODO: Check database for matching profiles
    match = ""

    for person in database:
        if (len(person)) == 4:
            counter = 0
            for i in range(len(person) - 1):
                if int(person[i + 1]) == longestsmall[i]:
                    counter += 1
                else:
                    i = range(len(person))
            if counter == 3:
                match = person[0]
                print(person[0])

        elif (len(person)) != 4:
            counter = 0
            for i in range(len(person) - 1):
                if int(person[i + 1]) == longestlarge[i]:
                    counter += 1
                else:
                    i = range(len(person))
            if counter == len(person) - 1:
                match = person[0]
                print(person[0])
    if match == "":
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
