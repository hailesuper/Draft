#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = tmp;
            image[i][j].rgbtGreen = tmp;
            image[i][j].rgbtRed = tmp;
        }
    }
    return;
}

// Convert image to sepia
int checktemp(int tmp)
{
    if (tmp > 255)
    {
        return 255;
    }
    else
    {
        return tmp;
    }
}
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //make sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            tmp = round(.393 * image[i][j].rgbtBlue) + round(.769 * image[i][j].rgbtGreen) + round(.189 * image[i][j].rgbtRed);
            image[i][j].rgbtRed = checktemp(tmp);

            //make sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            tmp = round(.349 * image[i][j].rgbtBlue) + round(.686 * image[i][j].rgbtGreen) + round(.168 * image[i][j].rgbtRed);
            image[i][j].rgbtGreen = checktemp(tmp);

            //make sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
            tmp = round(.272 * image[i][j].rgbtBlue) + round(.534 * image[i][j].rgbtGreen) + round(.131 * image[i][j].rgbtRed);
            image[i][j].rgbtBlue = checktemp(tmp);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0, midHeight = height; i < midHeight; i++)
    {
        for (int j = 0, midWidth = round(width / 2); j < midWidth; j++)
        {
            tmp = image[i][width - j];
            image[i][width - j] = image[i][j];
            image[i][j] = tmp;
        }
    }
    return;
}

// Blur image
bool valid(int a, int b, int height, int width)
{
    if (a >= 0 && b >= 0 && a <= height && b <= width)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0, sumGreen = 0, sumRed = 0, count = 0;
            for (int a = i - 1; a <= i + 1; a++)
            {
                for (int b = j - 1; b <= j + 1; b++)
                {
                    if (a >= 0 && b >= 0 && a <= height && b <= width)
                    {
                        sumBlue = sumBlue + image[a][b].rgbtBlue;
                        sumGreen = sumGreen + image[a][b].rgbtGreen;
                        sumRed = sumRed + image[a][b].rgbtRed;
                        count++;
                    }
                }
            }
            image[i][j].rgbtBlue = sumBlue / count;
            image[i][j].rgbtGreen = sumGreen / count;
            image[i][j].rgbtRed = sumRed / count;      
        }
    }
    return;
}
