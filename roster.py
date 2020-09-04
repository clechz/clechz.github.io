import csv
import cs50 
from sys import argv, exit

argc = len(argv)
if argc != 2:
    print("Usage: python import.py filename.csv")
    exit(1)
house = argv[1]    
db = cs50.SQL("sqlite:///students.db")    

rows = db.execute("SELECT * FROM students  WHERE house = ? ORDER BY last, first", house)

for row in rows:
    name = [row["first"], row["middle"], row["last"]]
    if name[1] == None:
        print(name[0]+" "+name[2]+",", end='')
    else:
        print(name[0]+" "+name[1] +" " +name[2]+",", end='')
    
    birth = row["birth"]
    print("born ",birth)

