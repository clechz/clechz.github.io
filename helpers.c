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
            int average = round(pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue / 3.0);
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
            int sepiaRed = cap(round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue));
            int sepiaGreen = cap(round(0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen + 0.168 * pixel.rgbtBlue));
            int sepiaBlue = cap(round(0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen + 0.131 * pixel.rgbtBlue));
            pixel.rgbtRed = sepiaRed;
            pixel.rgbtGreen = sepiaGreen;
            pixel.rgbtBlue = sepiaBlue;
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
    return
}
