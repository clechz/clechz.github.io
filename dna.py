# short tandem repeat/ str
from sys import argv, exit
import csv
# get max func :
def GetMax(s, sub):
    ans = [0] * len(s)
    ENOL = len(s) - len(sub)
    for i in range(ENOL, -1, -1):
        if s[i : i + len(sub)] == sub:
            if i + len(sub) > len(s) - 1:
                ans[i] = 1
            else:
                ans[i] = 1 + ans[i + len(sub)]
    return max(ans)        
def print_match(reader, actual):
    for line in reader:
        person = line[0]
        values = [ int(val) for val in line [1:] ] 
        if values == actual:
            print(person)
            return
    print("no match")    
# MAIN
argc =  len(argv)
if argc != 3:
    print("Usage:python dna.py csv(path)  STR.txt (file))")
    exit(1)

csv_path = argv[1]
txt_path = argv[2]
strc = 0
with open(csv_path,"r") as csvf:
    reader = csv.reader(csvf)
    allseq = next(reader)[1:]
    with open(txt_path,"r") as txtf:
        s = txtf.read()
        actual = [GetMax(s, seq) for seq in allseq]
    print_match(reader, actual)    

