#include<stdio.h>
#include<cs50.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
//modules.
int main(int argc, char **argv)
{
    bool isKeyValid = true;
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]); //"13">>13
    if (key < 0)
    {
        printf("key must be positve\n");
        return 1;
    }
    
    for (int l = 0; l < len; l++)
    {
        // If isdigit detects a non-digit it'll set our stored bool to false and end the loop
        if (isdigit(argv[1][l]) == false)
        {
            isKeyValid = false;
            l = len;
    }
    string plaintext = get_string("plaintext: "); //plai text input
    //loop
    printf("ciphertext: ");
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {


        if (islower(plaintext[i]))
        {
            printf("%c", (plaintext[i] - 'a' + key) % 26 + 'a');
        }
        else if (isupper(plaintext[i]))
        {
            printf("%c", (plaintext[i] - 'A' + key) % 26 + 'A');
        }
        else
        {
            printf("%c", plaintext[i]);
        }

    }
    printf("\n"); //new line
    
}




