#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
        char *word;
        struct node *next;	
} NODE;

typedef struct list {
        NODE* head;
        int size;
        char *code;
} LIST;

typedef struct {
        LIST **slot;
        int size;
        char letter;
} HASHTABLE;

LIST * emptyList();

int isEmpty(LIST *lisr);

void pushList(LIST *list, char *word);

char * popList(LIST *list);

HASHTABLE *  newhashtable(char letter, int wordsize);

char * wordToCode(char *word, char letter);

int codeCompare(char *code1, char *code2);

int codeToIndex(char *code,LIST **list, int size);

int findMaxSize(LIST **list, int size);

void pushHashtable(HASHTABLE *hst,char *word);

#endif

