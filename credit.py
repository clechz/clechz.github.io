from sys import exit
from cs50 import get_int

def check_sum(nums):
    sumls = []
    for j in range(len(nums)):
        j = -1
        j += 2
        sumls.append(nums[j])
    for s in range(len(nums)):
        r =  * 2
        s += 2
        if len(r) > 9:
            for i in range(len(r)):
                sumls.append([r[i]])
        else:
            sumls.append(r)
            
        fism = sum(sumls)
        if fism[-1] == 0:
            return fism
            
        else:
            print("INVALID")
            exit(0)
        
    return    
while True :
    nums = get_int("enter a credit card number: ")
    if nums >= 0:
        break
    

# nums counter
nums_count = 0
for i in range(len(nums)):
    nums_count += 1
# print output    
if nums_count == 15:
    print("AMEX")
    
elif nums_count == 16:
    print("MASTERCARD")
    
else:
    print("VISA")