#include<stdio.h>
#include<stdlib.h>

#include "math_util.h"

// https://projecteuler.net/problem=1
void SolveProblem_1(int n, int f1, int f2)
{
  int sum1 = MathUtil::SumOfMultiplesBelow(n, f1);
  int sum2 = MathUtil::SumOfMultiplesBelow(n, f2);
  int sum3 = MathUtil::SumOfMultiplesBelow(n, f1*f2);

  int result = sum1 + sum2 - sum3;
  printf("Result: %d\n", result);
}

// https://projecteuler.net/problem=2
void SolveProblem_2(int max)
{
  int a = 2, b = 1;
  int sum = 0;
  int step = 0;

  /*
    A_i = f(1 + 3*i);
    B_i = f(3*i);
    A_0 = 2;
    B_0 = 1;
    A_i = 3*A_(i-1) + 2*B_(i-1)
    B_i = 2*A_(i-1) + B_(i-1)
    =>
    B_i = A_(i-1) + A_(i-1) + B_(i-1);
    A_i = B_i + A_(i-1) + B_(i-1);
   */
  while (a <= max){
    step++;
    sum += a;
    int nextb = a + a + b;
    a = nextb + a + b;
    b = nextb;
  }
  printf("result:%d, step:%d\n", sum, step);
}
int main()
{
  //SolveProblem_1(1000, 3, 5);
  //SolveProblem_2(4000000);
}
