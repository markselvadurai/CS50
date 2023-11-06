#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            float avg = round(((image[x][y].rgbtRed + image[x][y].rgbtGreen + image[x][y].rgbtBlue) / 3.0));
            image[x][y].rgbtBlue = avg;
            image[x][y].rgbtRed = avg;
            image[x][y].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE bufferim[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            bufferim[x][y] = image[x][y];
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = bufferim[x][width-y-1];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE bufferim[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            bufferim[x][y] = image[x][y];
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            float redavg = 0;
            float blueavg = 0;
            float grnavg = 0;
            int counter = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (x+i >= 0 && y+j >= 0 && x+i < height && y+j < width)
                    {
                        redavg += image[x+i][y+j].rgbtRed;
                        blueavg += image[x+i][y+j].rgbtBlue;
                        grnavg += image[x+i][y+j].rgbtGreen;
                        counter ++;
                    }
                }
            }
            redavg = round(redavg/counter);
            blueavg = round(blueavg/counter);
            grnavg = round(grnavg/counter);

            bufferim[x][y].rgbtRed = redavg;
            bufferim[x][y].rgbtBlue = blueavg;
            bufferim[x][y].rgbtGreen = grnavg;
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = bufferim[x][y];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE bufferim[height][width];

    int gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};



    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            bufferim[x][y] = image[x][y];
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int redx = 0;
            int redy = 0;
            int greenx = 0;
            int greeny = 0;
            int bluex = 0;
            int bluey = 0;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (x + i - 1 < 0 || x + i - 1 > height - 1|| y + j - 1 < 0 || y + j - 1 > width - 1)
                    {
                        continue;
                    }
                    redx += image[x + i - 1][y + j - 1].rgbtRed * gx[i][j];
                    bluex += image[x + i - 1][y + j - 1].rgbtBlue * gx[i][j];
                    greenx += image[x + i - 1][y + j - 1].rgbtGreen * gx[i][j];

                    redy += image[x + i - 1][y + j - 1].rgbtRed * gy[i][j];
                    bluey += image[x + i - 1][y + j - 1].rgbtBlue * gy[i][j];
                    greeny += image[x + i - 1][y + j - 1].rgbtGreen * gy[i][j];
                }
            }

            int red = round(sqrt((redx * redx) + (redy * redy)));
            int green = round(sqrt((greenx * greenx) + (greeny * greeny)));
            int blue = round(sqrt((bluex * bluex) + (bluey * bluey)));

            if (red > 255)
            {
                red = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }

            bufferim[x][y].rgbtRed = red;
            bufferim[x][y].rgbtBlue = blue;
            bufferim[x][y].rgbtGreen = green;

        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = bufferim[x][y];
        }
    }

    return;
}
