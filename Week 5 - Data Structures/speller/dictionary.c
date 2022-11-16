// Implements a dictionary's functionality

#include <ctype.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Represents a node within a linked list within hash table, where we store two things, a word in a node and a pointer within that node to the next node
typedef struct node
{
    char word[LENGTH + 1];//character array which stores a word
    struct node *next; //pointer to next node
}
node;//lets us use just node in the rest of our program

//Number of buckets in hash table
const unsigned int N = 80;

// Hash table, an array of node pointers to linked lists which contain nodes, with N (NUMBER_OF_BUCKETS/ hash index/ linked lists) as its size.
node *table[N];

//variable to keep track of # of words in dictionary
int WordCount = 0;

// Returns true if word is in dictionary confirming it is spelled correctly, else false
bool check(const char *word)
{
    //Obtain hash index
    int hashindex = hash(word);

    //Acccesing linked list at that index in the hash table
    //p for pointer
    node *p = table[hashindex];

    while (p != NULL) // At the end of linked list we have NULL
    {
        //strcasecmp compares two strings and checks if word in question is in specific linked list checking every node
        if (strcasecmp(word, p-> word) == 0)
        {
            return true;
        }
        //go to next word in next node
        p = p -> next;
    }
    //if word is not present
    return false;
}

// Hashes word to a number, unsigned means positive
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory in hash table, returning true if successful, else false
bool load(const char *dictionary)
{
    //open dictionary file
    FILE *OpenDictionary = fopen(dictionary, "r");
    if (OpenDictionary == NULL)
    {
        return false;
    }

    // character array, read word into, where words are stored and from which words can be accessed
    char Word[LENGTH + 1];
    //Read strings from file using fscanf and returns EOF once it reaches end of file,
    //OpenDictionary is dictionary file and "Word" is character array where dictionary words will be put
    while (fscanf(OpenDictionary, "%s", Word) != EOF)
    {
        //use malloc to create memory for a new node which will store a word and pointer
        node *p = malloc(sizeof(node));
        if (p == NULL)
        {
            return false;//return false if not enough memory

        }
        //Copies Word into node word field using p->word of node created using strcpy function
        strcpy(p->word, Word);
        //Sets the pointer to next node
        p->next = NULL;
        //obtain index of given word using hash function so that index number can be used to index/insert node, just created, in the right linked list
        int hashindex = hash(Word);
        //Associating pointer p of new node being inserted with first/next node of the linked list at current index within hash table
        p->next = table[hashindex];
        // Associating new node with hash index obtained from word
        table[hashindex] = p;
        // Keep track of # of words
        WordCount++;

    }
    //close file
    fclose(OpenDictionary);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (WordCount > 0)
    {
        //Wordcount was tracked in Load function
        return WordCount;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
//Iterates through all buckets or index
    for (int i = 0; i < N; i++)
    {
        node *p = table[i]; // associating pointer with first node of indexed linked list
        while (p != NULL) // At the end of linked list we have NULL
        {
            node *tmp = p;//new node tmp pointer points at same location as p
            p = p -> next;// set p pointer to next node
            free(tmp); // free tmp
            table[i] = tmp;// set tmp to new first node of linked list
        }
    }
    return true;
}


