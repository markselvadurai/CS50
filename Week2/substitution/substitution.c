#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string cipher(string sub);
int main(int argc, string argv[])
{
    if (argv[1])
    {
        if (argv[2])
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        else if (strlen(argv[1]) == 26)
        {
            for (int i = 0; i < 26; i++)
            {
                for (int y = 26; y >= 0; y--)
                {
                    if (y == i)
                    {
                        y--;
                    }
                    else if (argv[1][i] == argv[1][y])
                    {
                        return 1;
                    }
                }
                if (!isalpha(argv[1][i]))
                {
                    return 1;
                }
            }
            printf("ciphertext: %s\n", cipher(argv[1]));
        }

        else if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}
string cipher(string sub)
{
    printf("%s\n", sub);
    string text = get_string("plaintext: ");
    int textlen = strlen(text);
    for (int i = 0; i < textlen; i++)
    {
        if (isupper(text[i]))
        {
            text[i] = toupper(sub[text[i] - 'A']);
        }
        else if (islower(text[i]))
        {
            text[i] = tolower(sub[text[i] - 'a']);
        }
    }
    return text;
}