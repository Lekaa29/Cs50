import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Wrong usage")

    # TODO: Read database file into a variable
    list = []
    large = 0
    if (sys.argv[1] == "databases/large.csv"):
        large = 1
        with open(sys.argv[1], "r") as file:
            reader = csv.DictReader(file)
            for row in reader:
                list.append({"name": row["name"], "AGATC": row["AGATC"], "TTTTTTCT": row["TTTTTTCT"], "AATG": row["AATG"],
                            "TCTAG": row["TCTAG"], "GATA": row["GATA"], "TATC": row["TATC"], "GAAA": row["GAAA"], "TCTG": row["TCTG"]})
    else:
        with open(sys.argv[1], "r") as file:
            reader = csv.DictReader(file)
            for row in reader:
                list.append({"name": row["name"], "AGATC": row["AGATC"], "AATG": row["AATG"], "TATC": row["TATC"]})

    # TODO: Read DNA sequence file into a variable
    if (large == 1):
        p = [0, 0, 0, 0, 0, 0, 0, 0]
        max = [0, 0, 0, 0, 0, 0, 0, 0]
        a = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]
        test = {
            "AGATC": 0,
            "TTTTTTCT": 0,
            "AATG": 0,
            "TCTAG": 0,
            "GATA": 0,
            "TATC": 0,
            "GAAA": 0,
            "TCTG": 0,
        }
    else:
        a = ["AGATC", "AATG", "TATC"]
        p = [0, 0, 0]
        max = [0, 0, 0]
        test = {
            "AGATC": 0,
            "AATG": 0,
            "TATC": 0,
        }

    with open(sys.argv[2], "r") as f:
        readertest = f.read(1)
        while (True):
            c = readertest
            for i in range(0, len(p)):
                if (c == a[i][p[i] % len(a[i])]):
                    p[i] += 1
                elif (c != a[i][p[i] % len(a[i])] and p[i] // len(a[i]) > 0):
                    if (max[i] < p[i] // len(a[i])):
                        max[i] = p[i] // len(a[i])
                    p[i] = 0
                else:
                    if (p[i] > 0):
                        if (c != a[i][p[i]-2]):
                            if (c == a[i][0]):
                                p[i] = 1
                            else:
                                p[i] = 0
                        else:
                            if (a[i][p[i]-2] != "T" and c != "T"):
                                if ((a[i][p[i]-2] != "A" and c != "A") or (a[i][p[i]-1] == "T" and c == "A")):
                                    p[i] -= 1

            readertest = f.read(1)
            if not readertest:
                break

    for i in range(0, len(p)):
        test[a[i]] = max[i]

    # TODO: Find longest match of each STR in DNA sequence

    # TODO: Check database for matching profiles
    result = 0
    count = 0
    for i in range(0, len(list)):
        for j in range(0, len(p)):
            if (int(list[i][a[j]]) == int(test[a[j]])):
                count += 1
        if (count == len(p)):

            print(list[i]["name"])
            result = 1
            break
        else:
            count = 0
    if (result == 0):
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
