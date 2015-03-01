#include<stdio.h>
#include<stdlib.h>

#include "math_util.h"

void PathSumTwoWays_81()
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
  minimal[0][0] = matrix[0][0];
  for (i = 1; i < row; i++) minimal[i][0] = matrix[i][0] + minimal[i-1][0];
  for (j = 1; j < column; j++) minimal[0][j] = matrix[0][j] + minimal[0][j-1];
  for (i = 1; i < row; i++)
    for (j = 1; j < column; j++){
      minimal[i][j] = (minimal[i][j-1] > minimal[i-1][j]) ? 
        minimal[i-1][j] : minimal[i][j-1];
      minimal[i][j] += matrix[i][j];
    }
  printf("%d\n", minimal[row-1][column-1]);
}

int main()
{
  PathSumTwoWays_81();
}
