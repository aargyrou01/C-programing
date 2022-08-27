#include<stdio.h>
#include<stdlib.h>
/**
 * @brief this method calulates the sum of all the array
 * @param h height of the array
 * @param w is the width of the array
 * @param arr is the array
 * @return the sum of the array
 */
int sumOfarray(int h, int w,int arr[][200]){
    int sum=0;
    for(int i=0;i<h;i++){
          for(int j=0;j<w;j++){
              sum=sum+arr[i][j];
          }
        }
        return sum;

}
/**
 * @brief prints the array
 * @param h height of the array
 * @param w is the width of the array
 * @param arr is the array
 * @return
 */
void printTable (int h, int w,int arr[][200]){
    for (int i=0; i<h;i++){
        for (int j=0; j<w; j++){
            printf("%d " , arr[i][j]  );
    }
    printf("\n");
    }
}

/**
 * @brief checks if the column is sorted in ascending
 * @param k is the height
 * @param j is the width
 * @param arr is the array
 *
 */
int ascendingColumn(int k, int j, int arr[][200]){
    for (int i=0; i<k; i++){
       if (!(arr[i][j]<arr[i+1][j])){
           return 0;
       }
    }
    return 1;
}

/**
 * @brief checks if the row is sorted ascending
 * @param h height of the array
 * @param w is the width of the array
 * @param arr is the array
 * @return gives back 1 if it is correctly ascenting and 0 if its not
 */
int ascendingrow(int i,int k, int arr[][200]){
    for (int j=0; j<k;j++){
        if (!(arr[i][j]<arr[i][j+1])){
            return 0;
        }
    }
    return 1;
}
/**
 * @brief the number is even
 * @param h height of the array
 * @param w is the width of the array
 * @param arr is the array
 * @param i position
 * @param j position
 * @return -1 if is odd
 */
int evenNum(int arr[][200], int h, int w, int i, int j){
    if(j!=0){
        if(i!=0)
            return evenUpLeft(arr,h,w,i,j);
        else
        {
            if(i!=h-1)
                return evenDownLeft(arr,h,w,i,j);
        }        
    }
    else {
        if(j!=w-1)
            if(i!=0)
                return evenUpRight(arr,h,w,i,j);
            else
            {
                if(i!=h-1)
                    return evenDownRight(arr,h,w,i,j);
            }
    }
 
    return -1;
 
}
/**
 * @brief the up left number is even
 * @param h height of the array
 * @param w is the width of the array
 * @param arr is the array
 * @param i position
 * @param j position
 * @return -1 if is odd
 */
int evenUpLeft(int arr[][200],int w, int h, int i, int j){
    if(arr[i-1][j-1]!=0){
     return arr[i-1][j-1]%2!=0;}
    return -1;
}
/**
 * @brief the down left number is even
 * @param h height of the array
 * @param w is the width of the array
 * @param arr is the array
 * @param i position
 * @param j position
 * @return -1 if is odd
 */
int evenDownLeft(int arr[][200], int w,int h, int i, int j){
    if(arr[i+1][j-1]!=0){
        return arr[i+1][j+1]%2!=0;
    }
    return -1;
}
/**
 * @brief the up right number is even
 * @param h height of the array
 * @param w is the width of the array
 * @param arr is the array
 * @param i position
 * @param j position
 * @return -1 if is odd
 */
int evenUpRight(int arr[][200],int w, int h, int i, int j){
    if(arr[i-1][j+1]!=0){
     return arr[i-1][j+1]%2!=0;}
    return -1;

}
/**
 * @brief the down right number is even
 * @param h height of the array
 * @param w is the width of the array
 * @param arr is the array
 * @param i position
 * @param j position
 * @return -1 if is odd
 */
int evenDownRight(int arr[][200],int w, int h, int i, int j ){
    if(arr[i+1][j+1]!=0){
     return arr[i+1][j+1]%2!=0;}
    return -1;

}
/**
 * @brief creates an array eith 0 and 1 for odd and even
 * @param arr is the array
 * @param i position
 * @param j position

 */
void OddOrEven(int i, int j,int arr[][200]){
int oddOrEven[i][j];
int even[i][j];
for(int k=0;k<i;k++){
  for(int l=0;l<j;l++){
    if(arr[0][0]%2==0){
      if(l%2==0){
      oddOrEven[k][l]==0;
      } else oddOrEven[k][l]==1;
    } else {if(l%2==0){
      oddOrEven[k][l]==1;
      } else
      oddOrEven[k][l]==0;
      }
}

}}
/**
 * @brief fills the array each time its finds 0
 * @param h height of the array
 * @param w is the width of the array
 * @param arr is the array

 */
int fillArray (int h, int w ,int arr[][200]){
    for(int i=0;i<h;i++){
          for(int j=0;j<w;j++){
              if(arr[i][j]==0){
                  arr[i][j]++;
              while(!ascendingrow(i,j,arr))
              arr[i][j]++;
              while(!ascendingColumn(i,j,arr))
              arr[i][j]++;
             
             // if(evenNum(arr,h,w,i,j))
             // arr[i][j]++;  
             }
     }
     printf("\n");
     

    }  
 
}

int check (int h, int w, int arr[][200]){
    for(int i=0;i<h;i++){
          for(int j=0;j<w;j++){
              if (!ascendingrow(i,j,arr) || !ascendingColumn(i,j,arr)  ){
              printf("%d" ,-1);
              exit(-1);}
              else
              {
                    printTable(h,w,arr);
                    printf("\n");
                    printf("%d",sumOfarray(h,w,arr));
                    exit(-1);
              }
          }
    }

}

int main(int argc, char *argv[]){
    if (argc<2){
        printf("\nNo input files\n");
        return 0;
    }

    FILE *inf=NULL;
    inf= fopen(argv[1],"r");
if (inf==NULL){
    printf("\nFile not found\n");
    exit(-1);
}
  int arr[200][200];
    for (int i=0; i<200; i++){
        for (int j=0; j<200; j++){
            arr[i][j]=0;
        }
    }
int h=0,w=0;
fscanf(inf,"%d" "%d",&h , &w);

//reads the table from the file
for (int i=0; i<h;i++){
    for (int j=0; j<w; j++){
        fscanf(inf, "%d",&arr[i][j]);
    }
}
printTable(h,w,arr);
fillArray(h,w,arr);
check(h,w,arr);
     

}
