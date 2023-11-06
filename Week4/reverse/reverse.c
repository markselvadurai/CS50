#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Incorrect usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1],"r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2],"w");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Read header
    // TODO #3
    WAVHEADER header;
    printf("%li\n",ftell(input));
    fread(&header, 44, 1, input);
    printf("%li\n",ftell(input));

    // Use check_format to ensure WAV format
    // TODO #4
    check_format(header);

    // Open output file for writing
    // TODO #5

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blocksize = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    WAVHEADER temp;
    fseek (input, 0, SEEK_END);
    while (ftell(input)-4 >= 44)
    {
        fseek (input, -1 * blocksize, SEEK_CUR);
        fread (&temp, blocksize, 1, input);
        fwrite (&temp, blocksize, 1, output);
        fseek (input, -1 * blocksize, SEEK_CUR);
    }

    printf ("%li\n", ftell (output));

}

int check_format(WAVHEADER header)
{
    // TODO #4
    char form[4] = {'W','A','V','E'};
    for (int x = 0; x < 4; x ++)
    {
        if (header.format[x] != form[x])
        {
            printf("Likely not a .wav file.\n");
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * (header.bitsPerSample / 8);
    printf("%i\n",block_size);
    return block_size;
}