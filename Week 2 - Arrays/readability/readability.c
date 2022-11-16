#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Counting functions for letters, words, sentences
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Assigning each counting function to a variable
    string text = get_string("Text: ");
    float l = count_letters(text);
    float w = count_words(text);
    float s = count_sentences(text);

    //using Coleman-Liau index and passing counting variables through it

    float index = 0.0588 * (l / w * 100) - 0.296 * (s / w * 100) - 15.8;
    int grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

//Defining counting functions

int count_letters(string text)
{
    int lettercount = 0;

    int len = strlen(text);
    for (int i = 0 ; i < len; i++)
        // Passing each character in the string through alpha function so that it determines if it is a letter
    {
        if (isalpha(text[i]))
        {
            lettercount += 1;
        }
    }
    return lettercount;
}

int count_words(string text)
{
    //Added one to wordcount variable bc there will be one more word than spaces

    int countwords = 1;

    int len = strlen(text);
    for (int i = 0 ; i < len; i++)

        // Passing each character in the string through aspace function so that it determines where the spaces are.
    {
        if (isspace(text[i]))
        {
            countwords += 1;
        }
    }
    return countwords;
}

// Passing each character in the string through to determines where the each line ends.

int count_sentences(string text)
{
    int sentences = 0;

    int len = strlen(text);
    for (int i = 0 ; i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }
    return sentences;
}
