#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            if (image[i][y].rgbtBlue == 0x00 && image[i][y].rgbtRed == 0x00 && image[i][y].rgbtGreen == 0x00)
            {
                image[i][y].rgbtBlue = 0xff;
            }
        }
    }

}
