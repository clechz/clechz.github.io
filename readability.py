from cs50 import get_string
s = get_string("Text: ").strip()
nol = 0
now = 0
nos = 0

for i in range(len(s)):
    if (i == 0 and s[i] != ' ' or i != len(s) - 1 and s[i] == ' ' and s[i + 1] != ' '):
        now += 1
        
    if s[i].isalpha():
        nol += 1
        
    if s[i] == '!' or s[i] == '.' or s[i] == '?':
        nos += 1
        
L = nol / now * 100
S = nos / now * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
if index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")