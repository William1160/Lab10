#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie *children[26];
    int end;
    int count;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    pTrie->end = 0;
    pTrie->count = 0;
    for (int i = 0; i < 26; i++)
    {
        pTrie->children[i] = NULL;
    }
    return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int length = strlen(word);
    for(int i = 0; i < length; i++)
    {
        int index = word[i] - 'a';
        if(pTrie->children[index] == NULL)
        {
            pTrie->children[index] = createTrie();
        }
        pTrie = pTrie->children[index];
    }
    if(pTrie->end == 0)
    {
        pTrie->end = 1;
        pTrie->count++;
    }
    else
    {
        pTrie->count++;
    }
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int length = strlen(word);
    for(int i = 0; i < length; i++)
    {
        int index = word[i] - 'a';
        if(pTrie->children[index] == NULL)
        {
            return 0;
        }
        pTrie = pTrie->children[index];
    }
    return pTrie->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < 26; i++)
    {
        if(pTrie->children[i] != NULL)
        {
            deallocateTrie(pTrie->children[i]);
            pTrie->children[i] = NULL;
            free(pTrie->children[i]);
        }  
    }
    free(pTrie);
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("file not found");
        return 0;
    }
    int numWords;
    fscanf(fp, "%d", &numWords);
    for (int i = 0; i < numWords; i++)
    {
        pInWords[i] = (char *)malloc(256*sizeof(char));
        fscanf(fp, "%s", pInWords[i]);
    }
    fclose(fp);
    return numWords;
}

int main(void)
{
    char *inWords[256];

    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}