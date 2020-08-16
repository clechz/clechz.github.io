#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width;j++)
    }
    RGBTRIPLE pixel = image[i][j];
    int average = round(pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue / 3.0)
    image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;

}
int mkf(int value);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
    }
    RGBTRIPLE pixel = image[i][j];
    int sepiaRed = round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue);
    int sepiaGreen = round(0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen + 0.168 * pixel.rgbtBlue);
    int sepiaBlue = round(0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen + 0.131 * pixel.rgbtBlue);
    pixel.rgbtRed = sepiaRed
    pixel.rgbtGreen = sepiaGreen
    pixel.rgbtBlue = sepiaBlue
    if(pixel.rgbtRed > 255)
    {
        mkf(pixel.rgbtRed)
    }
    if(pixel.rgbtGreen > 255)
    {
        mkf(pixel.rgbtGreen)
    }
    if(pixel.rgbtBlue > 255)
    {
        mkf(pixel.rgbtBlue)
    }
    int mkf(int value)
{
    value = 255;
    return value;
}
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
