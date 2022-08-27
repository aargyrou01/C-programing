#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 3

int isValid(short int arr[N][N]);
void printDirections();
void printTable (short int arr[N][N]);
int isSolution (short int arr[N][N]);
int isValidMove(short int arr[N][N], char move);
void play (short int arr[N][N]);
void readpuzzle(FILE *fp, short int arr [N][N]);
void curPos(short int arr[N][N], int *i, int *j);
void display( short int arr[N][N]);
void writePuzzle(char *name, short int arr[N][N]);

/**
 * @brief writes the puzzle in a new file
 * @param fn , the file name
 * @param arr , the solved puzzle
 * 
 */
void writePuzzle(char *name, short int arr[N][N]){
    char new[20] = "out-";
    strcpy(&new[4], name);
    FILE *fp = fopen(new, "w");

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            fprintf(fp,"%d\t",arr[i][j]);
        }
        fprintf(fp,"\n");
    }
    printf("Saving %s...Done\n", new);
    fclose(fp);
}


/**
 * @brief read the puzzle from the file
 * @param FILE , the file 
 * @param arr , the puzzle that its going to be filled from the file
 */
void readpuzzle(FILE *fp,short int arr[N][N]){
    
for (int i=0; i<N;i++){
    for (int j=0; j<N; j++){
        fscanf(fp, "%hd",&arr[i][j]);
    }
}

}
/**
 * @brief this function is were the actual game is played, it moves the puzzle
 * @param arr , the puzzle
 */
void play(short int arr [N][N]){
    int i,j;
    char move;
    printDirections();
    while(!isSolution(arr)){
	    do{
		display(arr);
		printf("move>");
		scanf("%s", &move);

	    }while(!isValidMove(arr,move));
	curPos(arr,&i,&j);
        if (move == 'u'){
                arr[i][j]=arr[i-1][j];
                arr[i-1][j]=0;
	}
	else if (move == 'd'){
                arr[i][j]=arr[i+1][j];
                arr[i+1][j]=0;
	}
	else if (move == 'l'){
                arr[i][j]=arr[i][j-1];
                arr[i][j-1]=0;

	}
	else if (move == 'r'){
                arr[i][j]=arr[i][j+1];
                arr[i][j+1]=0;
	}
	else if (move == 'e'){
		return;
	}
    }
    printf("Completed N-puzzle\n");
}       

/**
 * @brief checks if the move is valid
 * @param arr , the puzzle 
 * @param move , the move that the player choose
 * @return 1 , if the move is valid
 */
int isValidMove(short int arr[N][N], char move){
    int i, j;
    curPos(arr,&i,&j);
    if(move == 'u'){
        if(i!=0)
            return 1;

    }

    else if(move == 'd'){
	    if(i!=N-1)
            	return 1;
    }

    else if(move == 'l'){
        if(j != 0)
            return 1;
    }

    else if(move == 'r'){
        if(j!=N-1)
            return 1;
    }
    else if(move == 'e')
        return 1;

    printf("This is not a valid move\n");
    return 0;
   
}


/**
 * @brief checks if the puzzle is solved
 * @param arr is the puzzle
 * @return 1 if the array is sorted 
 * @return -1 if the array is not sorted
 */
int isSolution (short int arr [N][N]){
	if(arr[N-1][N-1] != 0)
		return 0;
	int counter = 1; 
	for (int i=0; i< N; i++ ){
		for (int j=0; j<N; j++){
			if (arr[i][j] != counter && arr[i][j]!=0 ){
                		return 0;
	    		}
			counter++;
       		 }
    	}
	return 1;
}

 /**
 * @brief finds the current possition of 0
 * @param arr , the puzzle 
 * @param x , the x possition
 * @param y, the y possition
 * @return the possition
 */
void curPos (short int arr [N][N], int *x, int *y){
     for (int i=0; i<N; i++){
         for (int j=0; j<N ; j++){
             if (arr[i][j]==0){
                 *x=i;
                 *y=j;
                 return;
             }
         }
     }
}

/**
 * @brief checks if the given puzzle is valid
 * @param arr , is the puzzle 
 * @return 0 if the puzzle is sorted
 * 
 */
int isValid( short int arr[N][N]){
    int buc[N*N];
    for(int i=0; i<N*N; i++){
        buc[i] = 0;
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(arr[i][j] > N*N || arr[i][j] < 0 || buc[arr[i][j]] != 0) return 0;
            buc[arr[i][j]]++; 
        }
    }

}


/**
 * @brief prints the directions of the game
 */
void printDirections(){
    printf("\n Enter your command in the following format: move>direction"
               "Notice: move> is the user prompt direction is one of: "
               "l(left), r(right), u(up), d(down), e(exit)\n");
}

/**
 * @brief prints the display of the puzzle
 * @param arr, the puzzle  
 */
void display(short int arr[N][N]){
    for (int i=0; i<N;i++){
    	printf("+-----+-----+-----+\n");
	printf("|");
        for (int j=0; j<N; j++){
            printf("  %d  |" , arr[i][j]  );
    	}
	printf("\n");
    }
    printf("+-----+-----+-----+\n");
}

/**
 * @brief the main part of the programm
 * @param argc
 * @param argv
 */
int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Usage: ./nPuzzle <game-file> \n");
        return 0;
    }

    FILE *fp = fopen(argv[1],"r");
    if (fp == NULL){
    	printf("\nFile not found\n");
        exit(-1);
    }
    short int arr[N][N];
    readpuzzle(fp, arr);

    if(!isValid(arr)){
    	printf("Not valid puzzle!\n");
	return 0;
    }
    play(arr);
    printf("\n Congratulations, you solved the 3-puzzle \n");
    writePuzzle(argv[1], arr);
    printf("\n Done...Bye!");


}


