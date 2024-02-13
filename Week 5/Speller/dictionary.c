// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int word_count = 0;

bool traverse_linked_list(const char *word, const node *node)
{
    if (strcasecmp(node->word, word) == 0)
    {
        return true;
    }

    if (node->next != NULL)
    {
        return traverse_linked_list(word, node->next);
    }

    return false;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hash_number = hash(word);
    const node *node_value = table[hash_number];

    if (node_value != NULL)
    {
        return traverse_linked_list(word, node_value);
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, word);
        int hash_number = hash(word);
        new_node->next = table[hash_number];
        table[hash_number] = new_node;
        word_count++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *node_value = table[i];
        while (node_value != NULL)
        {
            node *tmp = node_value;
            node_value = node_value->next;
            free(tmp);
        }
    }

    return true;
}
