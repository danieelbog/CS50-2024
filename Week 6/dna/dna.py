import csv
import sys


def main():

    # TODO: Check for command-line usage
    csv_filename = ""
    txt_filename = ""

    for i in range(len(sys.argv)):
        if (len(sys.argv) < 3):
            print("You didn't provide all needed command line arguments. Program will exit!")
            return
        csv_filename = sys.argv[1]
        txt_filename = sys.argv[2]

    # TODO: Read database file into a variable
    rows = []
    with open(csv_filename) as db_file:
        reader = csv.DictReader(db_file)
        for row in reader:
            rows.append(row)

    # TODO: Read DNA sequence file into a variable
    sequence = ""
    with open(txt_filename) as seq_file:
        reader = csv.DictReader(seq_file)
        sequence = reader.fieldnames[0]

    # TODO: Find longest match of each STR in DNA sequence
    dna = []
    for row in rows:
        for key in list(row.keys())[1:]:
            dna.append({key: longest_match(sequence, key)})
        break

    # TODO: Check database for matching profiles
    person_name = ""
    same_count = 0

    for row in rows:
        for molecule in dna:
            for key in molecule.keys():
                if (int(molecule.get(key)) == int(row.get(key))):
                    same_count += 1
                else:
                    same_count = 0
                if (same_count == len(dna)):
                    person_name = row.get("name")
                    break

    if (len(person_name) > 0):
        print(f"{person_name}")
    else:
        print("No match")


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
