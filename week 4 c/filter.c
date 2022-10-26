#include "helpers.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    float red;
    float green;
    float blue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;
            avg = (red + green + blue) / 3;
            image[i][j].rgbtRed = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtBlue = round(avg);
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int red;
    int green;
    int blue;
    if (width == 1)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                red = image[i][j].rgbtRed;
                image[i][j].rgbtRed = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue = red;
            }
        }
        return;
    }

    float x = width / 2.0;
    int n = round(x);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (image[i][j].rgbtBlue != image[i][width - 1 - j].rgbtBlue || image[i][j].rgbtRed != image[i][width - 1 - j].rgbtRed || image[i][j].rgbtGreen != image[i][width - 1 - j].rgbtGreen)
            {
                red = image[i][j].rgbtRed;
                green = image[i][j].rgbtGreen;
                blue = image[i][j].rgbtBlue;

                image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
                image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
                image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

                image[i][width - 1 - j].rgbtRed = red;
                image[i][width - 1 - j].rgbtGreen = green;
                image[i][width - 1 - j].rgbtBlue = blue;
            }
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float c;
    int sumr = 0;
    int red[height][width];
    int sumg = 0;
    int green[height][width];
    int sumb = 0;
    int blue[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i - 1) > - 1 && (j - 1) > -1)
            {
                sumr += image[i - 1][j - 1].rgbtRed;
                sumg += image[i - 1][j - 1].rgbtGreen;
                sumb += image[i - 1][j - 1].rgbtBlue;
                c++;
            }

            if ((i - 1) > - 1)
            {
                sumr += image[i - 1][j].rgbtRed;
                sumg += image[i - 1][j].rgbtGreen;
                sumb += image[i - 1][j].rgbtBlue;
                c++;
            }

            if ((i - 1) > - 1 && (j + 1) < width)
            {
                sumr += image[i - 1][j + 1].rgbtRed;
                sumg += image[i - 1][j + 1].rgbtGreen;
                sumb += image[i - 1][j + 1].rgbtBlue;
                c++;
            }

            if ((j - 1) > - 1)
            {
                sumr += image[i][j - 1].rgbtRed;
                sumg += image[i][j - 1].rgbtGreen;
                sumb += image[i][j - 1].rgbtBlue;
                c++;
            }

            sumr += image[i][j].rgbtRed;
            sumg += image[i][j].rgbtGreen;
            sumb += image[i][j].rgbtBlue;
            c++;

            if ((j + 1) < width)
            {
                sumr += image[i][j + 1].rgbtRed;
                sumg += image[i][j + 1].rgbtGreen;
                sumb += image[i][j + 1].rgbtBlue;
                c++;
            }
            if ((i + 1) < height && (j - 1) > - 1)
            {
                sumr += image[i + 1][j - 1].rgbtRed;
                sumg += image[i + 1][j - 1].rgbtGreen;
                sumb += image[i + 1][j - 1].rgbtBlue;
                c++;
            }

            if ((i + 1) < height)
            {
                sumr += image[i + 1][j].rgbtRed;
                sumg += image[i + 1][j].rgbtGreen;
                sumb += image[i + 1][j].rgbtBlue;
                c++;
            }

            if ((i + 1) < height && (j + 1) < width)
            {
                sumr += image[i + 1][j + 1].rgbtRed;
                sumg += image[i + 1][j + 1].rgbtGreen;
                sumb += image[i + 1][j + 1].rgbtBlue;
                c++;
            }

            red[i][j] = round(sumr / c);
            green[i][j] = round(sumg / c);
            blue[i][j] = round(sumb / c);
            c = 0;
            sumr = 0;
            sumg = 0;
            sumb = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = red[i][j];
            image[i][j].rgbtGreen = green[i][j];
            image[i][j].rgbtBlue = blue[i][j];
        }
    }

    return;
}

float squareOfNumber(float num)
{
    return (num * num);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int sumrx = 0;
    int sumry = 0;
    int redx[height][width];
    int redy[height][width];
    int sumgx = 0;
    int sumgy = 0;
    int greenx[height][width];
    int greeny[height][width];
    int sumbx = 0;
    int sumby = 0;
    int bluex[height][width];
    int bluey[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i - 1) > - 1 && (j - 1) > -1)
            {
                sumrx += (image[i - 1][j - 1].rgbtRed) * -1;
                sumgx += (image[i - 1][j - 1].rgbtGreen) * -1;
                sumbx += (image[i - 1][j - 1].rgbtBlue) * -1;

                sumry += (image[i - 1][j - 1].rgbtRed) * - 1;
                sumgy += (image[i - 1][j - 1].rgbtGreen) * - 1;
                sumby += (image[i - 1][j - 1].rgbtBlue) * - 1;

            }

            if ((i - 1) > - 1)
            {

                sumrx += (image[i - 1][j].rgbtRed) * 0;
                sumgx += (image[i - 1][j].rgbtGreen) * 0;
                sumbx += (image[i - 1][j].rgbtBlue) * 0;


                sumry += (image[i - 1][j].rgbtRed) * -2;
                sumgy += (image[i - 1][j].rgbtGreen) * -2;
                sumby += (image[i - 1][j].rgbtBlue) * -2;


            }

            if ((i - 1) > - 1 && (j + 1) < width)
            {
                sumrx += (image[i - 1][j + 1].rgbtRed) * 1;
                sumgx += (image[i - 1][j + 1].rgbtGreen) * 1;
                sumbx += (image[i - 1][j + 1].rgbtBlue) * 1;

                sumry += (image[i - 1][j + 1].rgbtRed) * - 1;
                sumgy += (image[i - 1][j + 1].rgbtGreen) * - 1;
                sumby += (image[i - 1][j + 1].rgbtBlue) * - 1;


            }

            if ((j - 1) > - 1)
            {
                sumrx += (image[i][j - 1].rgbtRed) * -2;
                sumgx += (image[i][j - 1].rgbtGreen) * -2;
                sumbx += (image[i][j - 1].rgbtBlue) * -2;

                sumry += (image[i][j - 1].rgbtRed) * 0;
                sumgy += (image[i][j - 1].rgbtGreen) * 0;
                sumby += (image[i][j - 1].rgbtBlue) * 0;



            }

            sumrx += (image[i][j].rgbtRed) * 0;
            sumgx += (image[i][j].rgbtGreen) * 0;
            sumbx += (image[i][j].rgbtBlue) * 0;


            sumry += (image[i][j].rgbtRed) * 0;
            sumgy += (image[i][j].rgbtGreen) * 0;
            sumby += (image[i][j].rgbtBlue) * 0;


            if ((j + 1) < width)
            {
                sumrx += (image[i][j + 1].rgbtRed) * 2;
                sumgx += (image[i][j + 1].rgbtGreen) * 2;
                sumbx += (image[i][j + 1].rgbtBlue) * 2;


                sumry += (image[i][j + 1].rgbtRed) * 0;
                sumgy += (image[i][j + 1].rgbtGreen) * 0;
                sumby += (image[i][j + 1].rgbtBlue) * 0;


            }
            if ((i + 1) < height && (j - 1) > - 1)
            {
                sumrx += (image[i + 1][j - 1].rgbtRed) * -1;
                sumgx += (image[i + 1][j - 1].rgbtGreen) * -1;
                sumbx += (image[i + 1][j - 1].rgbtBlue) * -1;

                sumry += (image[i + 1][j - 1].rgbtRed) * 1;
                sumgy += (image[i + 1][j - 1].rgbtGreen) * 1;
                sumby += (image[i + 1][j - 1].rgbtBlue) * 1;

            }

            if ((i + 1) < height)
            {

                sumrx += (image[i + 1][j].rgbtRed) * 0;
                sumgx += (image[i + 1][j].rgbtGreen) * 0;
                sumbx += (image[i + 1][j].rgbtBlue) * 0;


                sumry += (image[i + 1][j].rgbtRed) * 2;
                sumgy += (image[i + 1][j].rgbtGreen) * 2;
                sumby += (image[i + 1][j].rgbtBlue) * 2;

            }

            if ((i + 1) < height && (j + 1) < width)
            {
                sumrx += (image[i + 1][j + 1].rgbtRed) * 1;
                sumgx += (image[i + 1][j + 1].rgbtGreen) * 1;
                sumbx += (image[i + 1][j + 1].rgbtBlue) * 1;

                sumry += (image[i + 1][j + 1].rgbtRed) * 1;
                sumgy += (image[i + 1][j + 1].rgbtGreen) * 1;
                sumby += (image[i + 1][j + 1].rgbtBlue) * 1;
            }

            redx[i][j] = sumrx;
            redy[i][j] = sumry;
            greenx[i][j] = sumgx;
            greeny[i][j] = sumgy;
            bluex[i][j] = sumbx;
            bluey[i][j] = sumby;

            sumrx = 0;
            sumgx = 0;
            sumbx = 0;

            sumry = 0;
            sumgy = 0;
            sumby = 0;
        }
    }



    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((sqrt((squareOfNumber(redx[i][j])) + squareOfNumber(redy[i][j]))) < 256)
            {
                image[i][j].rgbtRed = round(sqrt((squareOfNumber(redx[i][j])) + squareOfNumber(redy[i][j])));
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }

            if ((sqrt((squareOfNumber(bluex[i][j])) + squareOfNumber(bluey[i][j]))) < 256)
            {
               image[i][j].rgbtBlue = round(sqrt((squareOfNumber(bluex[i][j])) + squareOfNumber(bluey[i][j])));
            }
            else
            {

                image[i][j].rgbtBlue = 255;
            }

            if ((sqrt((squareOfNumber(greenx[i][j])) + squareOfNumber(greeny[i][j]))) < 256)
            {
                image[i][j].rgbtGreen = round(sqrt((squareOfNumber(greenx[i][j])) + squareOfNumber(greeny[i][j])));
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }

        }
    }

    return;
}
