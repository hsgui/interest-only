#include<stdio.h>
#include<stdlib.h>

#include "math_util.h"

/*
  https://projecteuler.net/problem=82

  dynamic programming
  suppose minimal[i][j] stores the minimal path from first column
  to current element [i,j] (containing current element)  
     - very similar with the Dijkstra algorithm
  then we must have:
  minimal[i][j] = 
      min{minimal[i][j-1] + matrix[i][j], 
          minimal[i-1][j] + matrix[i][j], 
          minimal[i+1][j] + matrix[i][j]}
  
 */
void PathSumThreeWays_82()
{
  int row = 80, column = 80;
  int i, j;
  int matrix[row][column];
  for (i=0; i < row; i++)
    for (j = 0; j < column; j++){
      if (j < column - 1)
        scanf("%d,", &matrix[i][j]);
      else
        scanf("%d", &matrix[i][j]);
    }

  int minimal[row][column];
  // initial the first column
  for (i = 0; i < row; i++) minimal[i][0] = matrix[i][0];

  // in every loop, we get the minimal path of all elements in current column
  for (i = 1; i < column; i++){
    // see the element in the column
    for (j = 0; j < row; j++){
      minimal[j][i] = minimal[j][i-1] + matrix[j][i];
    }
    
    // the following is simple:
    // suppose we have a double linked list in both directions
    // then compute the minimal path to current element from some element
    // when we have only one element, then the minimal is itself.
    // when we have two elements, then, we need to check up and down
    // when we have three elements, compute the minimal path based on the two.
    for (j = 1; j < row; j++){
      if (minimal[j][i] > minimal[j-1][i] + matrix[j][i]){
        minimal[j][i] = minimal[j-1][i] + matrix[j][i];
      }
    }
    for (j = row-2; j >= 0; j--){
      if (minimal[j][i] > minimal[j+1][i] + matrix[j][i]){
        minimal[j][i] = minimal[j+1][i] + matrix[j][i];
      }
    }
  }
  int min = minimal[0][column-1];
  for (i = 1; i < row; i++){
    if (min > minimal[i][column-1]){
      min = minimal[i][column-1];
    }
  }

  printf("%d\n", min);
}

int main()
{
  PathSumThreeWays_82();
}
