import csv
import cs50 
from sys import argv, exit

# parse the fullname
def parse(fullname):
    names_list = fullname.split()
    return names_list 

argc = len(argv)
if argc != 2:
    print("Usage: python import.py filename.csv")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

with open(argv[1]) as inf:
    reader = csv.DictReader(inf)
    for row in reader:
        # parse func call
        fullname = parse(row["name"])
       
        # insert null to the tow names for a fullname
        if len(fullname) == 2:
            fullname.insert(1, None)
       
        # columns
        stname = fullname[0]
        midname = fullname[1]
        lasname = fullname[2]
        house = row["house"]
        birth = row["birth"]
        
        # ecuting the sql query: add .stname, midname, lasname, house, birth. to students table
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", 
            stname, midname, lasname, house, birth)
