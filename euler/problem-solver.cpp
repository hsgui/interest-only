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

// https://projecteuler.net/problem=5
void SolveProblem_5(unsigned int below, unsigned int up)
{
  unsigned int spn = up;
  unsigned int n = up - 1;

  while (n >= below){
    unsigned int next = n;
    n--;
    if (n >= below){
      // (n, n+1) must be coprime
      next *= n;
      n--;
    }
    spn = MathUtil::LCM(spn, next);
  }
  printf("result=%d, below=%d, up=%d\n", spn, below, up);
}

// https://projecteuler.net/problem=6
void SolveProblem_6(unsigned int n)
{
  unsigned int result = (n*n - 1) * (3*n*n +2*n)/12;
  printf("result=%d, n=%d\n", result, n);
}

void SolveProblem_7(unsigned int nth)
{
  unsigned int ith = 2;
  unsigned int num = 3;
  if (nth == 1) {
    ith = 1;
    num = 2;
  }
  // before the while, num is the ith prime
  while (ith < nth){
    num += 2;
    if (MathUtil::IsPrime(num)) ith++;
  }
  printf("nth=%d, prime:%d\n", nth, num);
}

void SolveProblem_9(unsigned int sum)
{
  unsigned int a, b, c;
  for (c = sum / 3 + 1; c < sum / 2; c++){
    for (b = (sum - c) / 2 + 1; b < c; b++){
      a = sum - b - c;
      if (a*a + b*b == c*c){
        printf("a=%d, b=%d, c=%d, sum=1000, product=%d\n", a, b, c, a*b*c); 
      }
    }
  }
}

/*
  https://projecteuler.net/problem=15
  route[row][column] = route[row-1][column] + route[row][column-1], row, column >=1;
  route[0][column] = 1, column >= 1;
  route[row][0] = 1, row >= 1;
 */
void LatticePaths_15(unsigned int row, unsigned int column)
{
  unsigned int rowIndex, columnIndex;
  // the paths may be very large. int is not enough
  unsigned long route[row+1][column+1];
  route[0][0] = 0;
  for (rowIndex = 1; rowIndex <= row; rowIndex++) route[rowIndex][0] = 1;
  for (columnIndex = 1; columnIndex <= column; columnIndex++) route[0][columnIndex] = 1;
  for (rowIndex = 1; rowIndex <= row; rowIndex++)
    for (columnIndex = 1; columnIndex <= column; columnIndex++){
      route[rowIndex][columnIndex] = route[rowIndex-1][columnIndex] + route[rowIndex][columnIndex-1];
    }
  printf("%d*%d lattice paths: %lu\n", row, column, route[row][column]);
}

void SelfPowers_48(unsigned int n, unsigned long m)
{
  unsigned int i, j;
  unsigned long remainder = 0;
  unsigned long modpower = 1;
  for (i = 1; i <= n; i++){
    modpower = 1;
    for (j = 1; j <= i; j++){
      modpower = MathUtil::ModMultiple(modpower, i, m);
    }
    remainder = MathUtil::ModAdd(remainder, modpower, m);
  }
  printf("%d mod %lu is %lu\n", n, m, remainder);
}

void PowerDigitSum_16(unsigned int exp)
{
  unsigned int digits[exp+1];
  unsigned int i, j;
  unsigned int length = 1;
  unsigned int carry = 0;
  for (i = 0; i <= exp; i++) digits[i] = 0;
  digits[0] = 1;
  for (i=1; i <= exp; i++){
    carry = 0;
    for (j = 0; j <= length-1; j++){
      carry = digits[j] * 2 + carry;
      digits[j] = carry % 10;
      carry = carry / 10;
    }
    if (carry > 0) digits[length++] = carry;
  }
  unsigned int sum = 0;
  for(i = 0; i <= exp; i++) sum += digits[i];

  printf("power digit sum of %d is %d\n", exp, sum);
}

void AmicableNumbers_21(unsigned int num)
{
  unsigned int sum = 0;
  unsigned int i = 1;
  for (i = 1; i < num; i++){
    unsigned int j = MathUtil::SumOfDivisors(i);
    if (i >= j) continue;
    if (i == MathUtil::SumOfDivisors(j)) {
      sum += i;
      sum += j;
      printf("find amicable numbers: %d, %d\n", i, j);
    }
  }
  printf("num=%d, sum=%d\n", num, sum);
}

int main()
{
  //SolveProblem_1(1000, 3, 5);
  //SolveProblem_2(4000000);
  //SolveProblem_3(600851475143);
  //SolveProblem_3(2);
  //SolveProblem_4(100, 999);
  //SolveProblem_5(1, 20);
  //SolveProblem_6(100);
  //SolveProblem_7(10001);
  //SolveProblem_9(1000);
  //LatticePaths_15(20, 20);
  //SelfPowers_48(1000, 10000000000);
  //PowerDigitSum_16(1000);
  AmicableNumbers_21(10000);
}

