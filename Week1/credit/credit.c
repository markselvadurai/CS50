#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool asking = true;

void invalid(void)
{
    printf("INVALID\n");
}

int main(void)
{
    //Initializing Variables
    long cardnum = get_long("Card Number: ");
    long digits = 0;
    long digitcheck = cardnum;
    int checksum = 0;
    long x = 0;
    long dig;
    long dig2;
    long newnum = cardnum;

    //Counting digits
    while (digitcheck > 0)
    {
        digitcheck = digitcheck / 10;
        digits++;
        //printf("Digits: %li\n", digits);
    }

    long p = pow(10, digits);

    //Finding values and using Luhn's Algorithm
    while (x < digits)
    {
        dig = newnum % 10;
        newnum = newnum / 10;
        dig2 = newnum % 10;
        newnum = newnum / 10;
        //printf("digit %li: %li\n",x,dig2);
        x += 2;
        if (dig2 * 2 >= 10)
        {
            checksum += dig2 * 2 % 10 + 1;
        }
        else
        {
            checksum += dig2 * 2;
        }
        checksum += dig;
    }
    float startingnums = floor(cardnum / pow(10, digits - 2));
    //printf("sum: %i\n",checksum);
    //printf("first digits: %f\n", startingnums );

    //Starting Verification, If numbers are valid for a card.
    if (checksum % 10 == 0)
    {
        //printf("PASSED");
        if (startingnums == 34 || startingnums == 37)
        {
            if (digits == 15)
            {
                printf("AMEX\n");
            }
            else
            {
                invalid();
            }
        }

        else if (startingnums == 51 || startingnums == 52 || startingnums == 53 || startingnums == 54 || startingnums == 55)
        {
            if (digits == 16)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                invalid();
            }
        }

        else if (floor(startingnums / 10) == 4)
        {
            if (digits == 16 || digits == 13)
            {
                printf("VISA\n");
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}