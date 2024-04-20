#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    for (int i = 0; i < height; i++)
    {
        for(int x = 0; x < width; x++)
        {
            average = round(((float) image[i][x].rgbtRed + (float) image[i][x].rgbtGreen + (float) image[i][x].rgbtBlue) / 3.0);
            image[i][x].rgbtRed = average;
            image[i][x].rgbtGreen = average;
            image[i][x].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed = 0;
    int originalGreen = 0;
    int originalBlue = 0;
    int newRed = 0;
    int newGreen = 0;
    int newBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for(int x = 0; x < width; x++)
        {
            originalRed = image[i][x].rgbtRed;
            originalGreen = image[i][x].rgbtGreen;
            originalBlue = image[i][x].rgbtBlue;
            newRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            newGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            newBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (newRed > 255)
            {
                image[i][x].rgbtRed = 255;
            }
            else
            {
                image[i][x].rgbtRed = newRed;
            }

            if (newGreen > 255)
            {
                image[i][x].rgbtGreen = 255;
            }
            else
            {
                image[i][x].rgbtGreen = newGreen;
            }

            if (newBlue > 255)
            {
                image[i][x].rgbtBlue = 255;
            }
            else
            {
                image[i][x].rgbtBlue = newBlue;
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int count = 0;
    int leftRGB[3] = {0, 0, 0};
    int rightRGB[3] = {0, 0, 0};;

    for (int i = 0; i < height; i++)
    {
        for(int x = 0; x < width / 2; x++)
        {
            leftRGB[0] = image[i][x].rgbtRed;
            leftRGB[1] = image[i][x].rgbtGreen;
            leftRGB[2] = image[i][x].rgbtBlue;

            rightRGB[0] = image[i][width - (x + 1)].rgbtRed;
            rightRGB[1] = image[i][width - (x + 1)].rgbtGreen;
            rightRGB[2] = image[i][width - (x + 1)].rgbtBlue;

            image[i][x].rgbtRed = rightRGB[0];
            image[i][x].rgbtGreen = rightRGB[1];
            image[i][x].rgbtBlue = rightRGB[2];

            image[i][width - (x + 1)].rgbtRed = leftRGB[0];
            image[i][width - (x + 1)].rgbtGreen = leftRGB[1];
            image[i][width - (x + 1)].rgbtBlue = leftRGB[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            copy[i][x].rgbtRed = image[i][x].rgbtRed;
            copy[i][x].rgbtGreen = image[i][x].rgbtGreen;
            copy[i][x].rgbtBlue = image[i][x].rgbtBlue;
        }
    }

    float averageRed = 0;
    float averageGreen = 0;
    float averageBlue = 0;
    float pixelCount = 0;

    // for every comlumn
    for (int i = 0; i < height; i++)
    {
        // go to the row
        for(int x = 0; x < width; x++)
        {
            averageRed = 0;
            averageGreen = 0;
            averageBlue = 0;
            pixelCount = 0;
            // and average all ajacent pixels
            for (int down = -1; down < 2; down++)
            {
                for (int over = -1; over < 2; over++)
                {
                    // this logic might be wrong check on this if buggy!
                    if (i + down >= 0 && i + down <= (height - 1) && x + over >= 0 && x + over <= (width - 1))
                    {
                        averageRed += copy[i + down][x + over].rgbtRed;
                        averageGreen += copy[i + down][x + over].rgbtGreen;
                        averageBlue += copy[i + down][x + over].rgbtBlue;
                        pixelCount++;
                    }
                }
            }
            averageRed /= (float) pixelCount;
            averageGreen /= (float) pixelCount;
            averageBlue /= (float) pixelCount;
            image[i][x].rgbtRed = round(averageRed);
            image[i][x].rgbtGreen = round(averageGreen);
            image[i][x].rgbtBlue = round(averageBlue);
        }
    }
    return;
}
