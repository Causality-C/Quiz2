#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/*
* Comparator Function
*/
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

/*
* Generates the table of all test cases 0->N
*/
int* generateDPTable(int * table, int LEN, int N){
    //Sort the Table
    qsort(table, LEN,sizeof(int),  cmpfunc);
    //Generate new table
    int ** dpTable = malloc((LEN+1)* sizeof(int*));
    for(int i = 0; i<= LEN; i++){
        //Allocate N+1 spots so that 0->N is shown
        dpTable[i] = malloc((N+1)* sizeof(int));
        //Zero elements means no possible values are reachable
        for(int j = 0; j<= N; j++){
            dpTable[i][j] = 0;
        }
        //It is always possible to get zero
        dpTable[i][0] = 1;
    }
    
    //Populate Table O(N*LEN)
    for(int i = 1; i<=LEN; i++){
        int val = table[i-1];
        for(int j = 1; j<= N; j++){
            if(j == val){
                dpTable[i][j] = 1;
            }
            else if(j<val){
                dpTable[i][j] = dpTable[i-1][j];
            }
            else{
                dpTable[i][j] = dpTable[i-1][j] | dpTable[i-1][j-val];
            }
        }
    }
    //Freeing all but return value (which is a row)
    int * ret = dpTable[LEN];
    for(int i= 0; i<LEN; i++){
        free(dpTable[i]);
    }
    free(dpTable);
    
    return ret;
}

/*
* Returns 1/true if subset sum is possible. 
* False otherwise O(1) querying
*/
int querySubset(int * table, int val, int N){
    //Out of bounds 
    if(val<0 || val>N){
        return 0;
    }
    return table[val];
}
/*
* Get the sum of an Array
*/
int arraySum(int * table, int N){
    int sum = 0;
    for(int i = 0; i< N; i++){
        sum += table[i];
    }
    return sum;
}
/*
* Print an Array given its length
*/
void printArray(int * arr, int N){
    printf("Printing Array\n");
    for(int i = 0; i< N; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void){
    int array[] = {1,6,8,5};
    int N = sizeof(array)/sizeof(int);
    printArray(array,N);
    int sum = arraySum(array, N);
    int *answers = generateDPTable(array,N,sum);
    //1 denotes that the sum is possible. 0 denotes that sum is impossible. 
    for(int i = 0; i<= sum; i++){
        printf("Is the Sum %d Possible : %d\n", i, querySubset(answers, i,sum));
    }
    //Outliers: Sums that are out of range 
    printf("Is the Sum %d Possible : %d\n", 100000, querySubset(answers, 100000,sum));
    printf("Is the Sum %d Possible : %d\n", -1, querySubset(answers, -1,sum));
    free(answers);
}