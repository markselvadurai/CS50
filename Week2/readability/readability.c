#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int level(string input);

int main(void)
{
    string text = get_string("Text: ");
    int grade = level(text);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", level(text));
    }
}

int level(string input)
{
    int letters = 0;
    int sentences = 0;
    int words = 1;
    int len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        input[i] = tolower(input[i]);
        if (input[i] >= 97)
        {
            letters++;
        }
        else if (input[i] == '!' || input[i] == '?' || input[i] == '.')
        {
            sentences++;
        }
        else if (input[i] == ' ')
        {
            words++;
        }
    }
    float L = (letters / (float)words) * 100;
    float S = (sentences / (float)words) * 100;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    return round((0.0588 * L) - (0.296 * S) - 15.8);
}