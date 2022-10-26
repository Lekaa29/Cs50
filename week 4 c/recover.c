#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <math.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        return 1;
    }


    uint8_t *start = malloc(5);


    BYTE buffer[512];




    start[0] = 0xff;
    start[1] = 0xd8;
    start[2] = 0xff;
    start[3] = 0xdf;
    start[4] = 0xef;



    int x = -1;


    char *filename = malloc(8);
    sprintf(filename, "%03i.jpg", 0);
    FILE *img = NULL;




    while (fread(buffer, sizeof(BYTE) * 512, 1, input) == 1)
    {
        if (buffer[0] == start[0] && buffer[1] == start[1] && buffer[2] == start[2] && buffer[3] > start[3] && buffer[3] <= start[4])
        {
            if(img != NULL)
            {
                fclose(img);
            }

            free(filename);
            filename = malloc(8);

            x++;
            sprintf(filename, "%03i.jpg", x);
            img = fopen(filename, "w");


        }

        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, img);
        }
    }


    if(img != NULL)
    {
        fclose(img);
    }

    fclose(input);

    free(start);
    free(filename);

    return 0;

}