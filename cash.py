from cs50 import get_float 
while True:
    dn = get_float("change owed: ")
    if dn >  0 or dn ==  0:
        break
cen = round(dn * 100)
coins = 0
while cen >= 25:
    coins += 1
    cen -= 25
    
while cen >= 10:
    coins += 1
    cen -= 10
    
while cen >= 5:
    coins += 1
    cen -= 5

while cen >= 1:
    coins += 1
    cen -= 1
    
print(coins)    