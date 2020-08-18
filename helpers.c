#include "helpers.h"
#include<math.h>
#include<cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel;
            pixel = image[i][j];
            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
}
int cap(int value)
{
    return value > 255 ? 255 : value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int orginalRed = pixel.rgbtRed;
            int orginalGreen = pixel.rgbtGreen;
            int orginalBlue = pixel.rgbtBlue;
            image[i][j].rgbtRed = cap(round(0.393 * orginalRed+ 0.769 * orginalGreen + 0.189 * orginalBlue));
            image[i][j].rgbtGreen = cap(round(0.349 * orginalRed+ 0.686 * orginalGreen + 0.168 * orginalBlue));;
            image[i][j].rgbtBlue = cap(round(0.272 *orginalRed+ 0.534 * orginalGreen + 0.131 * orginalBlue));;
        }
    }
}

void swap(RGBTRIPLE * pixel1, RGBTRIPLE * pixel2)
{
    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width -1 - j]);
        }
    }
}

bool isvap(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}
RGBTRIPLE blurpix(int i, int j, int height, int width,  RGBTRIPLE image[height][width])
{
    int redvalue, greenvalue, bluevalue; redvalue = greenvalue = bluevalue =0;
    int sumvapix = 0;
     for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int ni = i + di;
            int nj = j + dj;
            if(isvap(ni, nj, height, width))
            {
                sumvapix++;
                redvalue += image[ni][nj].rgbtRed;
                greenvalue += image[ni][nj].rgbtGreen;
                bluevalue += image[ni][nj].rgbtBlue;
            }
        }
    }
    RGBTRIPLE blurpix;
    blurpix.rgbtRed = round((float)redvalue / sumvapix);
    blurpix.rgbtGreen = round((float)greenvalue / sumvapix);
    blurpix.rgbtBlue = round((float)bluevalue / sumvapix);
    return blurpix;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE neimg[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            neimg[i][j] = blurpix(i, j, height, width, image);
        }   
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = neimg[i][j];
        }    

    }    
}    