from cs50 import get_float 
while(True):
    dn = get_float('change owed: ')
    if dn > 0.0:
        break
cen = round(dn * 100)
coins = 0
while cen > 25:
    coins += 1
    
while cen > 10:
    coins += 1    
    
while cen > 5:
    coins += 1

while cen > 1:
    coins += 1
    
print(coins)    