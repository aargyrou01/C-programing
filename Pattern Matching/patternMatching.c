#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 

int cnt(char *file);
int brutef(char dna[], char pat[],int dnalen,int patlen);
int KarpRabin(char dna[], char pat[], int dnalen, int patlen);
int Zalgorithm(char dna[], char pat[], int patlen, int dnalen);
int hash(char* word, int patlen);
int power(int base, int exp);

/**
 * @brief counts the length of each file
 * @param file , the file name
 * @return the number of characters in the file 
 * 
 */
int cnt(char *file){
    FILE *fp = fopen(file, "r");
    if (fp == NULL){
    	printf("\nFile not found\n");
        return 0;
    }

	int cnt=0;
    char ch;
    while ((fscanf(fp,"%c", &ch))!=EOF){
         cnt++;
    }

    fclose(fp);
    return cnt-1;   
}
/**
 * @brief this algorithm is searching if there is one or more M-groups of characters exactly the same within Y. it compares the first character of X with the
 *         equivalent of Y and moves on to the next until it finds all the patterns.
 * @param dna , the array with the dna
 * @param pat, the array with the pattern
 * @param dnalen, the length of the dna array
 * @param patlen , the length of the pattern array
 * @return the number of matching patterns
 */ 
int brutef(char dna[], char pat[],int dnalen,int patlen){
    int found=0;
    int cnt=0;
    for (int i=0; i<dnalen; i++){
        for (int j=0; j<patlen; j++){
            if (dna[i+j]== pat[j]){
            found++;
            }
            else{
                break;} 
        }
        if (found == patlen){
            cnt++;}
            found=0;
            
        }
        return cnt;
} 

/**
 * @brief finds the power
 * @param base, the base number
 * @param exp, the exponend of the number
 * @return the result
 */ 
int power(int base, int exp){
    if(exp != 0)
        return base*power(base, exp-1);
    return 1;
}

/**
 * @brief finds each characters hashing
 * @param word , the pattern
 * @param patlen , the length of the pattern
 * @return the hash value
 */ 
int hash(char *word, int patlen){
    int hashvalue = 0;
    for(int i=0; i<patlen; i++){
        hashvalue += (int)word[i]*(int)power(2,i);
    }
    return hashvalue % INT_MAX;
}

/**
 * @brief converse the the pattern to a hash and then compares the hash in order with the hash of the dna until the end of the dna sequence and 
 *          counts all the matching patterns with the dna.
 * @param dna , the dna array
 * @param pat , the pattern array
 * @param dnalen , dna length
 * @param patlen, pat length
 * @return the number of the matching patterns
 * 
 */ 
int KarpRabin(char dna[], char pat[], int dnalen, int patlen){
    int pathash = hash(pat, patlen);
    int counter = 0;
    for(int i= 0; i<dnalen-patlen+1; i++){
        if(pathash == hash(&dna[i],patlen)){
            int j;
            for(j=0;j<patlen; j++){
                if(dna[i+j] != pat[j])
                    break;
            }
            if(j == patlen)
                counter++;
        }
    }
    return counter;
}

/**
 * @brief  find the occurrence of a pattern in a string in linear time. the algorithm is to concatenate pattern and text,
 *  and create a string “P$T” where P is pattern, $ is a special character should not be present in pattern and text, and T is text.
 * In Z array, if Z value at any point is equal to pattern length, then pattern is present at that point
 * @param dna , the dna array
 * @param pat , the pattern array
 * @param dnalen , dna length
 * @param patlen, pat length
 * @return the number of the matching patterns
 * 
 */ 
int Zalgorithm(char dna[], char pat[], int patlen, int dnalen) {

	char* newStr = (char*)malloc((patlen + dnalen + 1) * sizeof(char)); 
	for (int i = 0; i < patlen; i++){
		newStr[i] = pat[i];
    }
    newStr[patlen] = '$';
	for (int j = 0; j < dnalen; j++){
		newStr[patlen+1+j] = dna[j];
    }

	int sizeOfnew = patlen + dnalen + 1;
	int zIndex[sizeOfnew];
	int cur = 0;

	for (int i = 1; i < sizeOfnew; i++) {
        cur = i;
		while (cur < sizeOfnew && newStr[cur - i] == newStr[cur])
				cur++;
		zIndex[i] = cur - i;
	}
	int found = 0;
	for (int j = 0; j < sizeOfnew; j++){
		if (zIndex[j] == patlen)
			found++;
    }

	return found;
}


/**
 * @brief the main part of the program. This is were it get from the arguments the instactions and 
 * does the right algorithms  
 * @param argc
 * @param argv
 */
int main(int argc, char *argv[]){
    int dnalen=cnt(argv[2]);
	int patlen=cnt(argv[3]);

 if (!(strcmp(argv[1],"-bf") || strcmp(argv[1],"-kp") || strcmp(argv[1],"-z"))) {
		printf("Wrong input"); 
		exit(-1);
	}

    FILE *fp = fopen(argv[2], "r");
    FILE *fp1= fopen(argv[3],"r");

    char dna[dnalen];
    char pat[patlen];

    for (int i=0; i<dnalen; i++){
        fscanf(fp, "%c",&dna[i]);
    }

    for (int i=0; i<patlen; i++){
        fscanf(fp1, "%c",&pat[i]);
    }


    fclose(fp);
    fclose(fp1);

    int num;
    if (strcmp(argv[1], "-bf")==0) {
		num = brutef(dna,pat,dnalen,patlen);
	}
	else if (strcmp(argv[1], "-kp") == 0) {
		num = KarpRabin(dna, pat,dnalen,patlen); 
	}
	else {
		num = Zalgorithm(dna,pat,patlen,dnalen); 
	}
	printf("The pattern was found:%d\t", num);
	printf("times\n");


} 