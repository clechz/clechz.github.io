# fav libary
from cs50 import get_float 
# user input
while True:
    dn = get_float("change owed: ")
    if dn > 0 or dn == 0:
        break
cen = round(dn * 100)  # num of cents in input
coins = 0  # coins needed
while cen >= 25:  # quarter
    coins += 1
    cen -= 25
    
while cen >= 10:  # dime
    coins += 1
    cen -= 10
    
while cen >= 5:  # 5 cents
    coins += 1
    cen -= 5

while cen >= 1:  # penny
    coins += 1
    cen -= 1
    
print(coins)    