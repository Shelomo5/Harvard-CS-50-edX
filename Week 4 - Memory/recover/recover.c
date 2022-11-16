#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Check usage has two arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE \n");
        return 1;
    }

//open memory card
    FILE *raw_file = fopen(argv[1], "r");
//ensures file can be read and that file pointer is returned and not null
    if (raw_file == NULL)
    {
        printf("image cannot be opened for reading \n");
        return 1;
    }

    // creating variable to keep track of number of JPEG files found
    int JPEG_count = 0;
    // Buffer is an array 512 bytes of memory
    BYTE buffer[512];
    //initializes file pointer for image files
    FILE *img_file = NULL;
    //allocate 8 characters of memory for the file name
    char filename[8];

//reading the memory card from a buffer
    while (fread(buffer, 1, 512, raw_file) == 512)
    {
        // scanning memory card for JPEGS
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //create new file for jpeg found
            sprintf(filename, "%03i.jpg", JPEG_count);

            //opening new file for found JPEG you can write data to
            img_file = fopen(filename, "w");

            JPEG_count++;
        }

        //write data to file
        if (img_file != NULL)
        {
            fwrite(buffer, 1, 512, img_file);
        }
    }

    //close file
    fclose(raw_file);
    fclose(img_file);

    return 0;
}


