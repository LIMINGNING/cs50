#include "helpers.h"
#include <math.h>

int Max255(int color);

int Max255(int color)
{
    if (color > 255)
        return 255;
    else
        return color;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            BYTE Average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);

            // Update pixel values
            image[i][j].rgbtBlue = Average;
            image[i][j].rgbtRed = Average;
            image[i][j].rgbtGreen = Average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            BYTE sepiaRed = Max255(round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                         .189 * image[i][j].rgbtBlue));
            BYTE sepiaGreen =
                Max255(round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                             .168 * image[i][j].rgbtBlue));
            BYTE sepiaBlue =
                Max255(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                             .131 * image[i][j].rgbtBlue));

            // Update pixel with sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    RGBTRIPLE temp_row[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_row[j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp_row[width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = temp_row[width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = temp_row[width - 1 - j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    sumRed += copy[i + k][j + l].rgbtRed;
                    sumGreen += copy[i + k][j + l].rgbtGreen;
                    sumBlue += copy[i + k][j + l].rgbtBlue;
                    count++;
                }
            }

            image[i][j].rgbtRed = (int) round(sumRed / count);
            image[i][j].rgbtGreen = (int) round(sumGreen / count);
            image[i][j].rgbtBlue = (int) round(sumBlue / count);
        }
    }

    return;
}
