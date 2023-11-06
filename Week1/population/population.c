#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size;
    int endsize;
    int years = 0;
    int population;

    // TODO: Prompt for start size
    do
    {
        size = get_int("Start size: ");
    }
    while (size < 9);
    // TODO: Prompt for end size
    do
    {
        endsize = get_int("End size: ");
    }
    while (endsize < size);
    // TODO: Calculate number of years until we reach threshold
    population = size;
    while (population < endsize)
    {
        int growth = population / 3;
        int decline = population / 4;
        population += growth - decline;
        years ++;
    }
    // TODO: Print number of years
    printf("Years: %d\n", years);
}
