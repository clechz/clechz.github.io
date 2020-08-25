from cs50 import get_int
# user`s input
while True:
    n = get_int("Height: ")
    if n >= 1 and n <= 8:
        break
k = 1  # icrement of hashes
s = n - 1  # num of spaces
# all of the nested loops

for i in range(1, n+1, 1):
    for s in range(s):
        print(' ', end='')
    s -= 1   
    for j in range(k):
        print("#", end='')
    k += 1
    s += 1
    print()