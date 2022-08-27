#include <stdio.h>
#include <stdlib.h>
#include "myHASHTABLE.h"
#include "Hangman.h"

static int sow = 0; //size of words

/**
 * @brief is the firts thing the program does. It reads the words and puts the words in the hashtable with the pushHashtable 
 * @param fp the file
 * @param hst the hashtable
 * 
 * */
LIST * firstTry(FILE *fp, HASHTABLE *hst){
	char *s = (char*)malloc((sizeof(char)*sow)+1);
	while(!feof(fp)){
		fscanf(fp,"%s",s);
		if(s == NULL)
			printf("Error\n");
		for(int i=0;i<sow;i++){
			if(s[i] >= 'A' && s[i] <= 'Z')
				s[i] = s[i] - 'A' + 'a';
		}
		pushHashtable(hst,s);		
	}
	int index = findMaxSize(hst->slot, hst->size);
	return hst->slot[index];
}

LIST * letterTry(HASHTABLE *hst, LIST *max){
	while(max->size > 0){
		pushHashtable(hst, popList(max));
	}
	return hst->slot[findMaxSize(hst->slot, hst->size)];

}
int codeToProg(char letter, char *code, char *prog){
	int chng = 0; //changed
	int cnt = 0; //counter

	int i=0;
	while(i<sow){
		if(prog[i] == '0'){
			cnt++;
			if(code[i] != '0'){
				chng++;
				prog[i] = letter;
			}
		}
		i++;
	}
	if(cnt == chng)
		return 1;
	else if(chng != 0)
		return -1;
	return 0;
}
/**
*@brief this method is the most important its were the game is played actualy. It prints the right messages to the user each time they play and for each letter they give
Also it checks if the letteer that the user gave is okay
*@param fp the file
*@param wordsize size of the word
*@param guesses is the guesses that the user have
*/
void playGame(FILE *fp, int wordsize, int guesses){
	sow = wordsize;
	int cnt = 0 , numwords=0 , foundword = 0;
	char letter;
	int correct = 0;
	int repletter = 0;
	char * code = NULL;
	char * prog = (char *)malloc(sizeof(char)*sow);
int k=0;
	while(k<sow){
		prog[k] = '0';
		k++;
	}
	LIST * maxs = NULL;
	while(cnt < guesses && correct != 1){
		printf("\n-------------------------------\n");
		if(cnt!=0){
			printf("Words possible %d\n",maxs->size);
		}
		printf("Progress: ");
		for(int i=0;i<sow;i++){
			if(prog[i] == '0')
				printf("_");
			else 
				printf("%c",prog[i]);
		}
		printf("\nNumber of Guesses: %d\n",guesses-cnt);
		printf("Guess a letter: ");
		scanf(" %c",&letter);

		if(letter > 'A' && letter < 'Z')
			letter = letter - 'A' + 'a';
		printf("\n");

		repletter = 0;
		int j;
		while(j<sow){
			if(prog[j] != '0' && prog[j] == letter)
				repletter = 1;
				j++;
		}

		HASHTABLE *newhst = newhashtable(letter, sow);
		if(repletter)
			printf("Letter %c was given before\n",letter);

		else{
			if(cnt == 0)
				maxs = firstTry(fp, newhst);
		
			else{

				LIST *temp = maxs;
				maxs = letterTry(newhst, maxs);
				free(temp);
				
			}	
			numwords = maxs->size;
			code = maxs->code;
			correct =  codeToProg(letter,code,prog);
			if(!correct)
				printf("%c not in secret word\n",letter);
			else
				printf("You guessed a letter correctly\n");

			free(newhst);

			if(!correct)
				cnt++;
		}
	
	} 	
	if(correct){
		printf("**************************************************\n");
		printf("Congratulations, you win the game\n");
		printf("The secret word is: ");
		int t=0;
		while(t<sow){
			printf("%c",prog[t]);
			t++;}
		printf("\n**************************************************\n");
	}
	if(cnt == guesses && !correct){
		printf("**************************************************\n");
		printf("You run out of guesses. You lost\n");
		printf("The secret word was: ");
		int c=0;
		while(c<sow){
			printf("%c",maxs->head->word[c]);
			c++;
		}
		printf("\n**************************************************\n");
		
	}

}
