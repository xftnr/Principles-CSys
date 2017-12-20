//Name: Pengdi Xia
//EID: px353

/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]){
  //initialize the variables
  int blocksize;
  int rowblock, colblock;
  int i,j;
  int temp=0,dia=0;
  //for different M,N have different optimized blocksize
  if(M==61){
    blocksize=16;
  }
  else if(M==32){
    blocksize=8;
  }
  // to optimized the 64*64 matrix I use another way to transpose it
  else if(M==64){
    //initialize the blocksize and temp variables
    blocksize=8;
    int a1,a2,a3,a4,a5,a6,a7,a0;
    //use the blocksize 8*8
    for(colblock=0; colblock<M; colblock+=blocksize){
		   for(rowblock=0; rowblock<N; rowblock+=blocksize){
         //divided the whole matrix into 4 blocks
         //read from up left down to bottom
	        for(i=0; i<8; i++){
            a0 = A[rowblock+i][colblock+0];
            a1 = A[rowblock+i][colblock+1];
            a2 = A[rowblock+i][colblock+2];
            a3 = A[rowblock+i][colblock+3];
            //save 4 more variables to use in futurn
            if(!i){
              a4 = A[rowblock][colblock+4];
					    a5 = A[rowblock][colblock+5];
              a6 = A[rowblock][colblock+6];
					    a7 = A[rowblock][colblock+7];
				    }
            //change the 4 B matrix block into temp variables
            B[colblock+0][rowblock+i] = a0;
            B[colblock+1][rowblock+i] = a1;
            B[colblock+2][rowblock+i] = a2;
            B[colblock+3][rowblock+i] = a3;
			    }
          //read down right up to top
          for(i = 7; i > 0; i--){
            a0 = A[rowblock+i][colblock+4];
				    a1 = A[rowblock+i][colblock+5];
				    a2 = A[rowblock+i][colblock+6];
				    a3 = A[rowblock+i][colblock+7];
				    B[colblock+4][rowblock+i] = a0;
				    B[colblock+5][rowblock+i] = a1;
				    B[colblock+6][rowblock+i] = a2;
				    B[colblock+7][rowblock+i] = a3;
			    }
          // we write the saved variables to B
          B[colblock+4][rowblock] = a4;
          B[colblock+5][rowblock] = a5;
          B[colblock+6][rowblock] = a6;
          B[colblock+7][rowblock] = a7;
		   }
		}
    //since we need terminate the program after 64*64 so we return here.
    return;
  }
  else{
    blocksize=4;
  }
  //the standard way to call the blocks
  for(colblock=0; colblock<N; colblock+=blocksize){
    for(rowblock=0; rowblock<M; rowblock+=blocksize){
      //set up the block that we can save the cache
      for(i=colblock; i<colblock+blocksize && i<N; ++i){
        for(j=rowblock; j<rowblock+blocksize && j<M; ++j){
          //transpose A to B
          if( i!=j){
            B[j][i]=A[i][j];
          }
          // we save the diagonal block into temp since we do not need to
          // change the position of these data.
          else {
            temp=A[j][j];
            dia=j;
          }
        }
        // at the end we copy back the data that loacate at the diagonal
        if(colblock==rowblock && i<N){
          B[dia][dia]=temp;
        }
      }
    }
  }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
