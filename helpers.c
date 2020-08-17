#include "helpers.h"
#include<math.h>

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

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int counter = 0;
    int sumGreen = 0;
    int sumRed = 0;
    int sumBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int m = j - 1; m <= j + 1; m++)
                {
                    if (k >= 0 && m >= 0 && k <= height && m <= width)
                    {
                        sumGreen += image[k][m].rgbtGreen;
                        sumBlue += image[k][m].rgbtBlue;
                        sumRed += image[k][m].rgbtRed;
                        counter++;
                    }
                }
            }
            image[i][j].rgbtGreen = sumGreen / counter;
            image[i][j].rgbtBlue = sumBlue / counter;
            image[i][j].rgbtRed = sumRed / counter;
            counter = 0;
            sumGreen = 0;
            sumBlue = 0;
            sumRed = 0;
        }
    }
    return;
}