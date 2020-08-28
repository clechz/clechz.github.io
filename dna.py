from sys import argv, exit
import sys
import csv

# checks for 2 command lines exactly
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

else:
    # open csv file, storing it as a list
    with open(sys.argv[1], newline='') as csv_file:
        datareader = csv.reader(csv_file)
        # Row1 contains the sequences of DNA to be read
        row1 = next(datareader)

        # open text file
        with open(sys.argv[2], 'r') as file:
            sreader = file.read()

            # an empty list, for storing the highest counts of each sequence
            counter = []

            # iterate through every DNA sequence to be counted
            for i in range(1, len(row1)):
                occurance = 0
                for c in sreader:
                    n = 1

                    # if find a sequence in text file, keep finding until it ends
                    while row1[i]*n in sreader:
                        n += 1

                    # update occurance only if 2nd seq longer than 1st seq
                    if (n - 1) > occurance:
                        occurance = n - 1

                # add the highest number of occurance into list counter
                counter.append(occurance)

            # condition to check if go through all text file and have not found object
            found = False
            for row in datareader:
                for c in range(len(counter)):

                    # if any element or csv row does not match the list counter, skip to next row
                    if int(row[c+1]) != int(counter[c]):
                        break

                    # if we reach the last element and loop is still not broken, this means this is the row required
                    elif c == (len(counter)-1):
                        print(row[0])
                        found = True
                        break

            # if go through and have not found anything
            if found == False:
                print("No match")