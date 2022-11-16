#include <stdio.h>
#include <cs50.h>

int main(void)
//associating question answer to a string variable which is then passed into the print function
{
    string name = get_string("what's your name? ");

    printf("hello, %s\n", name);
}