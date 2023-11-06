#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < height + 3 + y; x++)
        {
            if (x < height && y + x >= height - 1)
            {
                printf("#");
            }

            else if (x > height + 1 && x - y <= height + 2)
            {
                printf("#");
            }

            else
            {
                printf(" ");
            }

        }

        printf("\n");
    }
}