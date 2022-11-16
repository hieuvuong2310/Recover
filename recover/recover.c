#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        exit(1);
    }
    FILE *file = fopen(argv[1], "r"); //open the input file
    BYTE bytes[512]; // generate space
    char name[8];
    int count = 0;
    sprintf(name, "%03i.jpg", count);
    FILE *recover_file = fopen(name, "w"); // initialize the recover file
    while (fread(bytes, sizeof(BYTE), 512, file)) // read the file
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0) // check the start of new jpeg 
        {
            if (count == 0)
            {
                fclose(recover_file);
                sprintf(name, "%03i.jpg", count);
                recover_file = fopen(name, "w"); // 000.jpg
                count++;
            }
            else
            {
                fclose(recover_file);
                sprintf(name, "%03i.jpg", count); // next image
                recover_file = fopen(name, "w");
                count++;
            }
        }
        fwrite(bytes, sizeof(BYTE), 512, recover_file); // write to the file
    }
    fclose(recover_file);
    fclose(file);
    return 0;
}