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
RGBTRIPLE blurred(int h, int w, RGBTRIPLE original[h][w], int k, int m, int rows, int columns);

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        //Blur Corners
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                new_image[i][j] = blurred(height, width, image, 0, 0, 2, 2);
            }
            else if (i == 0 && j == width - 1)
            {
                new_image[i][j] = blurred(height, width, image, 0, width - 2, 2, 2);
            }
            else if (i == height - 1 && j == 0)
            {
                new_image[i][j] = blurred(height, width, image, height - 2, 0, 2 , 2);
            }
            else if (i == height - 1 && j == width - 1)
            {
                new_image[i][j] = blurred(height, width, image, height - 2, width - 2, 2, 2);
            }
            
            //Blur edges
            else if (i == 0 && ((j != 0) || (j != width - 1)))
            {
                new_image[i][j] = blurred(height, width, image, 0, j - 1, 2, 3);
            }
            else if (i == height - 1 && ((j != 0) || (j != width - 1)))
            {
                new_image[i][j]  = blurred(height, width, image, height - 2, j - 1, 2, 3);
            }
            else if (j == 0 && ((i != 0) || (i != height - 1)))
            {
                 new_image[i][j] = blurred(height, width, image, i - 1, 0, 3, 2);
            }
            else if (j == width - 1 && ((i != 0) || (i != height - 1)))
            {
                new_image[i][j] = blurred(height, width, image, i - 1, width - 2, 3, 2);
            }
            
            //Blur middle
            else
            {
                new_image[i][j] = blurred(height, width, image, i - 1, j - 1, 3, 3);
            }
        }
    }
    image = new_image;
    return;
}

//Calculates blur values INPUT: (original image, (start index of top left pixel in box) k, m, no. rows, no. columns)
RGBTRIPLE blurred(int h, int w, RGBTRIPLE original[h][w], int k, int m, int rows, int columns)
{
    long sum_red = 0;
    long sum_green = 0;
    long sum_blue = 0;
    float sum_counter = 0;
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            sum_red += original[k + i][m + j].rgbtRed;
            sum_green += original[k + i][m + j].rgbtGreen;
            sum_blue += original[k + i][m + j].rgbtBlue;
            sum_counter++;
        }
    }
    
    
    RGBTRIPLE image_blurred;
    image_blurred.rgbtRed = round(sum_red / sum_counter);
    image_blurred.rgbtGreen = round(sum_green / sum_counter);
    image_blurred.rgbtBlue = round(sum_blue / sum_counter);
    
    return image_blurred;
}
