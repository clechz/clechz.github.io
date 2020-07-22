#include<cs50.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>


int main(int argc, char** argv)
{
    
    int key = atoi(argv[1]); //"13">>13

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    if (key < 0)
    {
        printf("key must be positve\n");
        return 1;
    }

    
    string plaintext = get_string("plaintext: ");


    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        char c = plaintext[i];

        if(islower(c))
        {
            printf("%c", (c - 'a' + key) % 26 + 'a');
        }
        else if(isupper(c))
        {
            printf("%c", (c - 'A' + key) % 26 + 'A');          
        }
        else
        {
            printf("%c", c);
        }    
    }
    printf("\n");
}


