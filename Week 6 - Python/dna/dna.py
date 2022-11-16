import csv
import sys
from sys import argv, exit


def main():

    # Check that command-line doesn't exceed 3 arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # open the DNA sequence and read its contents into memory using function .read()
    with open(argv[2], "r") as txtfile:
        sequence = txtfile.read()

    # open the CSV file and read its contents into memory using DicrReader producing
    # a dictionary (csvreader) where the keys are the names of the columns
    with open(argv[1], "r") as csvfile:
        csvreader = csv.DictReader(csvfile)

        # Putting subsequences headers into a variable and removing "name" header, the first column
        strsubs = csvreader.fieldnames[1:]
        # intializing a dictionary where we can store the longest string of each STR repeats
        # within a given DNA sequence
        subsequences_longest_repeat_values = {}

    # Using longest_match function output to store/ associate longest repeat value for each STRs into
    # a dictionary by using a forloop to iterate over each subsequence in strsubs
        for subsequence in strsubs:
            subsequences_longest_repeat_values[subsequence] = longest_match(sequence, subsequence)
        # print(subsequences_longest_repeat_values)

    # iterating through each row of csv dictionary "csvreader" including names to find matching pattern of STRs
        for profile in csvreader:
            # Initiating a match variable
            match = True
            # iterating through each type of subsequence in strsubs
            for subsequence in strsubs:
                # subsequence repeat values of an individual/each row in csvreader database dictionary are compared with STR
                # values in the dictionary (csvreader) obtained from dna sequence. Every iteration checks that
                # match is false, that there's no match
                if int(profile[subsequence]) != subsequences_longest_repeat_values[subsequence]:
                    match = False
            # If there's a match then the name is printed
            if match:
                # accessing name of match in csvreader dictionary using "name" key
                name = profile["name"]
                print(name)
                exit(0)
        # if there's no match then no match is printed
        print("no match")


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


# if __name__ == "__main__":
main()

