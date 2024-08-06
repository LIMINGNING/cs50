#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define PIECE 512

int main(int argc, char *argv[])
{
    char filename[8];
    int PhotoCount = 0;

    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Can not open the file!");
        return 2;
    }

    // Create a buffer for a block of data
    uint8_t buffer[PIECE];

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, PIECE, card) == PIECE)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (PhotoCount == 1)
            {
                sprintf(filename, "%03i.jpg", PhotoCount);
                FILE *imageFile = fopen(filename, "w");
                fwrite(buffer, 1, PIECE, imageFile);
                fclose(imageFile);
            }
            else
            {
                sprintf(filename, "%03i.jpg", PhotoCount);
                FILE *imageFile = fopen(filename, "w");
                fwrite(buffer, 1, PIECE, imageFile);
                fclose(imageFile);
            }
            PhotoCount++;
        }
        else if (PhotoCount != 0)
        {
            FILE *imageFile = fopen(filename, "a");
            fwrite(buffer, 1, PIECE, imageFile);
            fclose(imageFile);
        }
    }
    fclose(card);
    printf("contagem = %i\n", PhotoCount);
}
