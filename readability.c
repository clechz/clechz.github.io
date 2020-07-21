#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int main(void)
{


    string s = get_string("Text: ");
    int wn,sn,ln;
    wn = sn = ln = 0;


    for(int i = 0, len = strlen(s); i < len; len++)
    {
        if(isalpha(s[i]))
            ln++;

        if((i = 0 && s[i] != ' ')
        ||(s[i] == ' ' && s[i + 1] != ' '))
            wn++;


        if(s[i] == '.' || s[i] == '!' || s[i] == '?')
            sn++;

    }

    float L = (ln / (float) wn) * 100;
    float S = (sn / (float) wn) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if(index <= 1)
        printf("Grade Before 1\n");

    else if(index >= 16 )
        printf("Grade 16+\n");

    else
        printf("Grade %i\n", index);

}