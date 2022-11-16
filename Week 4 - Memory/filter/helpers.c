#include <math.h>
#include "helpers.h"
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int grayscale;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //find avg of colors to get graycale then set each color to it
            grayscale = (round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0));
            image[i][j].rgbtRed = grayscale;
            image[i][j].rgbtGreen = grayscale;
            image[i][j].rgbtBlue = grayscale;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //using sepia equation to convert each color to its sepia value
            sepiaRed = round((image[i][j].rgbtRed * .393) + (image[i][j].rgbtGreen * .769) + (image[i][j].rgbtBlue * .189));
            sepiaGreen = round((image[i][j].rgbtRed * .349) + (image[i][j].rgbtGreen * .686) + (image[i][j].rgbtBlue * .168));
            sepiaBlue = round((image[i][j].rgbtRed * .272) + (image[i][j].rgbtGreen * .534) + (image[i][j].rgbtBlue * .131));

//Making sure value doesn't exceed 255
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // reflection array
    RGBTRIPLE imagereflection;
    for (int i = 0; i < height; i++)
    {
        //divide by two bc only swaping half the pixels on one side with pixels on other side
        for (int j = 0; j < (width / 2); j++)
        {
            // subtract 1 because it's an array that starts at 0
            imagereflection = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = imagereflection;
        }
    }
    return;
}

// Blur image
//When implementing the blur function, you might find that blurring one pixel ends up affecting the blur of another pixel.Perhaps create a copy of
//image (the function’s third argument) by declaring a new (two-dimensional) array with code like RGBTRIPLE copy[height][width];
//and copying image into copy, pixel by pixel, with nested for loops? And then read pixels’ colors from copy but write (i.e., change) pixels’
//colors in image?

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create blurred array so image array is maintained
    RGBTRIPLE copy[height][width];

//initianlizing variables where sumcount is total count of pixels and the other variables are the total pizels for each respective color
    float sumcount;
    int redcount;
    int greencount;
    int bluecount;

//For loops to identify every pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumcount = 0;
            redcount = 0;
            greencount = 0;
            bluecount  = 0;

            //for loops to identify neighboring pixels r (rows) is used to identify pixels above and below a row
            //and c (coloumns) is used to identify pixels once colum to the left and right of a given pixel
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    //selecting against neighboring pixels that are not within the image boundaries
                    if (((i + r) > (height - 1)) || ((i + r) < 0) || ((j + c) > (width - 1)) || ((j + c) < 0))
                    {
                        continue;//
                    }

                    //adding pixel values for each color and total pixel count
                    redcount += image[(i + r)][(j + c)].rgbtRed;
                    greencount += image[(i + r)][(j + c)].rgbtGreen;
                    bluecount  += image[(i + r)][(j + c)].rgbtBlue;
                    sumcount++;//
                }

            }
            //find average of each color to know what color value each pixel will have
            copy[i][j].rgbtRed = round(redcount / sumcount);
            copy[i][j].rgbtGreen = round(greencount / sumcount);
            copy[i][j].rgbtBlue = round(bluecount / sumcount);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //copy back to orginal array to make blur
            image[i][j] = copy[i][j];
        }
    }
    return;
}
