// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 27;

// Hash table
node *root;

int CountWords = 0;




char wordx[LENGTH + 1];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int i = 0;

    node *next = root->children[hash(&word[i])];

    i++;

    while (word[i] != 0)
    {
        if (next->children[hash(&word[i])] != NULL)
        {
            next = next->children[hash(&word[i])];
        }
        else
        {
            return false;
        }

        i++;

    }

    if (next->is_word == 1)
    {
        return true;
    }

    return false;


}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (word[0] != 39)
    {
        return tolower(word[0]) - 'a';
    }
    else
    {
        return 26;
    }

}

// Loads dictionary into memory, returning true if successful, else false
node *newnode()
{
    struct node *new = NULL;

    new = calloc(1, sizeof(node));

    new->is_word = 0;



    return new;

}

node *insert(node *rootx, char *word)
{
    node *tmp = rootx;


    for (int i = 0; tolower(wordx[i]) > 1; i++)
    {
        if (tmp->children[hash(&wordx[i])] == NULL)
        {
            tmp->children[hash(&wordx[i])] = newnode();
        }
        else
        {

        }

        tmp = tmp->children[hash(&wordx[i])];

    }

    CountWords++;
    tmp->is_word = 1;


    return rootx;

}


bool load(const char *dictionary)
{
    // TODO
    FILE *input = fopen(dictionary, "r");


    if (input == NULL)
    {
        return false;
    }

    root = newnode();

    while (fscanf(input, "%s", wordx) != EOF)
    {
        root = insert(root, wordx);
    }

    fclose(input);

    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return CountWords;
}

// Unloads dictionary from memory, returning true if successful, else false
void unl(node *un)
{
    for (int j = 0; j > 28; j++)
    {

        if (un->children[j] != NULL)
        {
            unl(un->children[j]);
        }

    }

    free(un);

    return;

}

bool unload(void)
{
    // TODO

    unl(root);

    return true;

}
