#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // h reprents height of pyramid desired by user
    int h;

    // do loop checks whether user input is between 1-8 or repeats
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    // For loop checks that r never exceeds h and adds a row every iteration
    for (int r = 0; r < h ; r++)
    {
        // For loop checks that s is always positive or 0 and subtracts a space for every iteration
        for (int s = h - r; s > 1; s--)
        {
            //print space
            printf(" ");
        }
        // For loops that checks that the number of hashes is never greater than the number of rows
        for (int c = -1 ; c < r; c++)
        {
            //print brick
            printf("#");
        }
        //move to next row
        printf("\n");
    }
}