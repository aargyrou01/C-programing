#include <stdio.h>
#include <stdlib.h>
#include "myHASHTABLE.h"

static int sizeofword = 0;

/**
 * @brief allocates the needed memory and creating an empty list
 * @return the new list
 * 
*/
LIST * emptyList(){
	LIST *newList = (LIST *)malloc(sizeof(LIST));
	newList->head = NULL;
	newList->size = 0;
	newList->code = NULL;
	return newList;
}

int isEmpty(LIST *list){
	return list->size == 0;
}

/**
 * @brief adds a new word into the list
 * @param list the list that was created before
 * @param word the word that will be added
 * */
void pushList(LIST *list, char *word){
	NODE *newnode = (NODE *)malloc(sizeof(NODE));
	newnode->word = (char *)malloc(sizeofword*sizeof(char));
	if(newnode == NULL)
		printf("No memory\n");
	for(int i=0; i<sizeofword;i++)
		newnode->word[i] = word[i];	
	if(isEmpty(list)){ //checks is the list is empty
		newnode->next = NULL;
		list->head = newnode;
		list->size++;
		return;	
	}
	newnode->next = list->head;
	list->head = newnode;
	list->size++;

}
/**
 * @brief deletes the needed data
 * @param list the list that was created before
 * @return the data that are still in the list
 * */
char * popList(LIST *list){
	if(isEmpty(list)){
		return NULL;
	}
	NODE *temp = list->head;
	char *data = list->head->word;
	list->size--;
	list->head = list->head->next;
	temp->next = NULL;
	free(temp);
	return data;
}
/***
 * @brief creates a new hashtable
 * @param letter that the user gives each time
 * @param wordlen is the length of the word
 * @return the new hashtable
 * 
*/
HASHTABLE * newhashtable(char letter, int wordlen){
	sizeofword = wordlen;
	HASHTABLE *newhst = (HASHTABLE *)malloc(sizeof(HASHTABLE));
	int arrsize = 1;
	for(int i=0;i<=sizeofword;i++)
		arrsize*=2;
	newhst->slot = (LIST **)malloc(arrsize * sizeof(LIST *));
	newhst->size = 0;
	newhst->letter = letter;
	return newhst;
}
/**
 * @brief codes a word with 0 and 1. at the postinion of the letter it puts 1 else 0
 * @param word the given word
 * @param letter form the player
 * @return the coded word
*/
char * codeToKey(char *word, char letter){
	char *code = (char *)malloc(sizeofword*sizeof(char));
	for(int i=0;i<sizeofword;i++){
		if(word[i] == letter)
			code[i] = '1';
		else
			code[i] = '0';
	}
	return code;
}
/**
 * @brief cheks is the code of 2 words is the same
 * @param code1 the 1st coded word
 * @param code2 the 2nd coded word
 * */
int codeCompare(char *code1, char *code2){
	for(int i=0;i<sizeofword;i++){
		if(code1[i] == code2[i])
			return 1;
	}
	return 0;
}

int codeToIndex(char *code,LIST **list,int size){
	for(int i=0;i<size;i++){
		if(codeCompare(code,list[i]->code))
				return i;
	}
	return -1;

}
/**
 * @brief gives back the number of the biggest group 
 * @param list the current list
 * @param size is the size of that list
 * @return cnt is the index
 * */
int findMaxSize(LIST **mylist, int size){
	int max = 0;
	int cnt= -1;
	for(int i=0;i<size;i++){
		if(mylist[i]->size >= max){
			max = mylist[i]->size;
			cnt = i;
		}
	}
	return cnt;

}
/**
 * @brief this method is the one that inserts any word in the hashtable
 * @param hst is the Hashtable 
 * @param word is the word the needed to be inserted to the hahtable
 * 
 * */ 
void pushHashtable(HASHTABLE *hst,char *word){
	char *code = wordToCode(word, hst->letter);
	int index = codeToIndex(code,hst->slot,hst->size); 
	if(index != -1){
		pushList(hst->slot[index], word);
	}
	else{
		hst->slot[hst->size] = emptyList();
		hst->slot[hst->size]->code = code;
		pushList(hst->slot[hst->size], word);
		hst->size++;
		
	}
	return;

}

