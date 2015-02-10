#include<stdio.h>
#include<stdlib.h>

#include "math_util.h"

/*
  https://projecteuler.net/problem=18
  https://projecteuler.net/problem=67
  maxsum[i, j] = max(maxsum[i-1, j], maxsum[i, j-1]), i,j >=1
  maxsum[0, j] = triangle[0, j] + maxsum[0, j-1]; j>=1
  maxsum[i, 0] = triangle[i, 0] + maxsum[i-1, 0]; i>=1
  maxsum[0, 0] = triangle[0, 0]
 */
void MaximumPathSum(unsigned int triangle[][100], unsigned int row)
{
  unsigned int column = row;
  unsigned int maximumSum[row][column];
  unsigned int rowIndex, columnIndex;
  maximumSum[0][0] = triangle[0][0];
  for (rowIndex = 1; rowIndex < row; rowIndex++) 
    maximumSum[rowIndex][0] = triangle[rowIndex][0] + maximumSum[rowIndex-1][0];
  for (columnIndex = 1; columnIndex < column; columnIndex++) 
    maximumSum[0][columnIndex] = triangle[0][columnIndex] + maximumSum[0][columnIndex-1];
  for (rowIndex = 1; rowIndex < row; rowIndex++)
    for (columnIndex = 1; columnIndex < row - rowIndex; columnIndex++){
      maximumSum[rowIndex][columnIndex] = 
        ((maximumSum[rowIndex-1][columnIndex] > maximumSum[rowIndex][columnIndex-1]) ? 
          maximumSum[rowIndex-1][columnIndex] : maximumSum[rowIndex][columnIndex-1]) + 
          triangle[rowIndex][columnIndex];
    }
  unsigned int max = 0;
  for (rowIndex = 0; rowIndex < row; rowIndex++){
    max = (max < maximumSum[rowIndex][row-rowIndex-1]) ? 
      maximumSum[rowIndex][row-rowIndex-1] : max;
  }
  printf("max is %d\n", max);
}

void ReadTriangle(unsigned int triangle[][100], unsigned int row)
{
  unsigned int i, j;
  for (i = 0; i < row; i++)
    for (j = 0; j <= i; j++){
      scanf("%d", &triangle[i-j][j]);
    }
}

int main()
{
  unsigned int row = 100;
  unsigned int triangle[row][100];
  ReadTriangle(triangle, row);
  MaximumPathSum(triangle, row);
}
