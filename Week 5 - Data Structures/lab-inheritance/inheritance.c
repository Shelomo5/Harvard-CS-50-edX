// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles. Each person has an array of two parents, each of which is a pointer to another person struct.
// Each person also has an array of two alleles, each of which is a char (either 'A', 'B', or 'O').
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations, for child with two generations of parents,`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *p = malloc(sizeof(person));

    // If there are still generations left to create, person has parents
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family, one fewer generation than what we started with
        //tree with one fewer generation so cal creat family genration function on generation - 1. store pointer p inside array parent 0
        //Remember, to access a variable via a pointer, we can use arrow notation.
        //For example, if p is a pointer to a person, then a pointer to this person’s first parent can be accessed by p->parents[0]
        //we do it twice because we need two parents.
        p -> parents[0] = create_family(generations - 1);
        p -> parents [1] = create_family(generations - 1);

        // TODO: Set parent pointers for current person


        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        // using p to access parents alleles we can randomly assign an allele, alleles is an array of two characters
        //%2 is mod 2 which means if number is even we get 0 and if number is odd we get 1, halft time we get value of 0 and the other half a 1
        // then we store it inside the child's allele array p-> on the left a random allele from first parent then we repeat same thing for second parent

        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];

    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // TODO: Randomly assign alleles
        p ->alleles[0] = random_allele();
        p ->alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    return p;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case, it means there's nothing left to free
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
