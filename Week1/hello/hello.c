#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string first = get_string("What is your first name\n");
    printf("Hello, %s .\n", first);
}
