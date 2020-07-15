#include <cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    float dollar;
    int cents, coins; // all variabels
    do
    {
        dollar = get_float("enter your change:"); // users change input
    }
    while (dollar <= 0);
    
    cents = round(dollar * 100);
    coins = 0; //variabels assignment 
    
    while (cents >= 25) //25 cents
    {
        cents -= 25;
        coins++;
    }
    while (cents >= 10) //10 cents
    {
        
        cents -= 10;
        coins++;
    }
    while (cents >= 5) //5 cents
    {
        
        cents -= 5;
        coins++;
    }
    while (cents >= 1) // 1 cent
    {
        
        cents -= 1;
        coins++;
    }

    printf("you will need at least %i coins\n", coins); //coins output  
    
}
