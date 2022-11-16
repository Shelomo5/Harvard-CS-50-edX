#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Pseudocode
//Accept single command line argument called k for the key
//Make sure program executed with only one command line argument that's a digit
//Output plain text to prompt user to get plain text from user
//encipher or decrypt plain text to get ciphertext
//Output ciphertext with each letter shifted by k
//print new line and exit

int main(int argc, string argv[])
{
    // Checking to see there's only one command line argument
    // argv is where different strings are stored including user key

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    // run for loop to pass each character in the key to ensure using each digit the key is a number and there's no letters
    {
        for (int i = 0, len = strlen(argv[1]); i < len; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
//atoi - convert a string to an int, so we're converting the key from a string to integer
    int n = atoi(argv[1]);

//prompts user for plain text
    string ptext = get_string("plaintext: ");

//Run loop to convert ptext character to enciphered characters
    printf("ciphertext: ");
    int len = strlen(ptext);
    for (int i = 0 ; i < len ; i++)
    {
        if (isupper(ptext[i]))
        {
        //Value of 'A' is 65,  we use these to convert to alphabetical index so we can apply key and then reconvert to ascii and print character
            printf("%c", ((((ptext[i] - 'A') + n) % 26) + 'A'));
        }
        else if (islower(ptext[i]))
        {
            //value of 'a' is 97
            printf("%c", ((((ptext[i] - 'a') + n) % 26) + 'a'));
        }
        else
        {
            printf("%c", ptext[i]);
        }
    }
    printf("\n");
    return 0;
}


