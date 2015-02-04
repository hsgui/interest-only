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

// https://projecteuler.net/problem=3
void SolveProblem_3(unsigned long num)
{
  unsigned long remain = num;
  unsigned long largestPrimeFactor = 1;
  unsigned long factor = 2;
  
  /*
    A = a_1^(n_1) * a_2^(n_2) * a_3^(n_3) * a_4^(n_4) * ... * a_k^(n_k);
    2 <= a_1 < a_2 < a_3 < a_4 < a_k, are primes
    1 <= n_1, n_2, n_3, n_4, ..., n_k;

    at some time point, we know that:
    B = a_1^(n_1) * a_2^(n_2) * a_3^(n_3'), n_3' < n_3;
    remain = a_3^(n_3 - n_3') * a_4^(n_4) * ... a_k^(n_k);
    A = B * remain;

    lpf(A) = max(lpf(B), lpf(remain)) = lpf(remain);
   */
  while (remain != 1){
    if (remain % factor == 0){
      // factor must be a_1, a_2, a_3, a_4, ..., a_k orderly;
      largestPrimeFactor = factor;
      remain /= factor;
    }else{
      factor = (factor == 2)? 3 : (factor + 2);
    }
  }
  
  printf("num:%lu, largestPrimeFactor:%lu\n", num, largestPrimeFactor);
}

// https://projecteuler.net/problem=4
void SolveProblem_4(unsigned int min, unsigned int max)
{
  unsigned int a, b;
  unsigned int maxPalindrome = 0;
  for (a = min; a <= max; a++){
    for (b = a; b <= max; b++){
      unsigned int product = a * b;
      if (MathUtil::IsPalindrome(product) && product > maxPalindrome){
        maxPalindrome = product;
      }
    }
  }
  printf("result=%d\n", maxPalindrome);
}

int main()
{
  //SolveProblem_1(1000, 3, 5);
  //SolveProblem_2(4000000);
  //SolveProblem_3(600851475143);
  //SolveProblem_3(2);
  //SolveProblem_4(100, 999);
}
