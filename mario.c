#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int height, row, column, space;
    do 
    {
        height = get_int("enter heigt here: ");
    }
    while (height < 1 || height > 8);  //the users height input
    
    
    for (row = 0; row < height; row++)// row loop is the loop that all they anthor loops is nested below it  and it adds new lines.
    {
        
        
        for (column = 0; column <= row ; column++) // adds # 
        {
            printf("#");
        }
    
        printf("\n");
    }
    
    

    
}
