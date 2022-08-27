#ifndef HANGMAN_H
#define HANGMAN_H


#include <stdio.h>
#include <stdlib.h>
#include "myHASHTABLE.h"

LIST * firstTry(FILE *fp, HASHTABLE *hs);

LIST * letterTry(HASHTABLE *hp, LIST *maxSlot);

int keyToProg(char letter, char *key, char *prog);

void printToUser( char letter, int correct);

void playGame(FILE *fp, int wsize, int guesses);

#endif
