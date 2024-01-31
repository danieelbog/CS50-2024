#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("The card could not be oppened...\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    char fileName[8];
    int file_count = 0;
    bool already_writing = false;

    while (fread(&buffer, BLOCK_SIZE, 1, card))
    {
        if (already_writing)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                file_count++;

                sprintf(fileName, "%03i.jpg", file_count);
                FILE *img = fopen(fileName, "w");

                fwrite(buffer, BLOCK_SIZE, 1, img);
                fclose(img);
            }
            else
            {
                FILE *img = fopen(fileName, "a");
                fwrite(buffer, BLOCK_SIZE, 1, img);
                fclose(img);
            }
        }
        else if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(fileName, "%03i.jpg", file_count);
            FILE *img = fopen(fileName, "w");

            fwrite(buffer, BLOCK_SIZE, 1, img);
            fclose(img);

            already_writing = true;
        }
    }

    fclose(card);
}
