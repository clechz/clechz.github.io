//standred libarys.
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
//to be more clear
#define FILE_NAME_SIZE 8
#define BLOCKSIZE 512
//for every byte
typedef uint8_t BYTE;

bool is_jpg(BYTE buffer[]);
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(" Usage: ./recover image\n");
        return 1;
    }
    FILE *inf = fopen(argv[1], "r");
    if (inf == NULL)
    {
        printf("invalid file %s !", argv[1]);
        return 1; 
    }
    BYTE buffer[BLOCKSIZE];
    int filx = 0;
    bool ffj = false;
    FILE *outfile;
    //loop over every block
    while (fread(buffer, BLOCKSIZE, 1, inf))
    {
        if (is_jpg(buffer))
        {
            if (!ffj)
            {
                ffj = true;
            }
            else
            {
                fclose(outfile);
            }    
            char filename[FILE_NAME_SIZE];
            sprintf(filename, "%03i.jpg", filx++);
            outfile = fopen(filename, "w");
            if (outfile == NULL)
            {
                return 1;
            }    
            fwrite(buffer, BLOCKSIZE, 1, outfile); 
        }
        
        else if (ffj)
        {
            fwrite(buffer, BLOCKSIZE, 1, outfile);
        }
        
    }
    //imp closing file
    fclose(outfile);
    fclose(inf);
    //sucsesfuly done !!
    return 0;
}
//is a jpeg function
bool is_jpg(BYTE buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}
//the end (by abdullah)