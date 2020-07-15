#include <cs50.h>
#include<stdio.h>
#include<math.h>

int main (void)
{
    float dollar;
    int cents, coins;
    do
    {
    dollar = get_float ("enter your change:");
    }
    while (dollar <= 0);
    
    cents = round (dollar*100);
    coins = 0;
    
    while (cents >= 25)
    {
       cents -= 25;
       coins++;
    }
    while (cents >= 10)
    {
        
        cents -= 10;
        coins++;
    }
    while (cents >= 5)
    {
        
        cents -= 5;
        coins++;
    }
    while (cents >= 1)
    {
        
        cents -= 1;
        coins++;
    }

   printf ("you will need at least %i coins\n", coins);
    
}
