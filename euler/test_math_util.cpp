#include<stdio.h>
#include<stdlib.h>

#include "math_util.h"

void testIsPalindrome()
{
  printf("3 is a palindrome: %d\n", MathUtil::IsPalindrome(3));
  printf("11 is a palindrome: %d\n", MathUtil::IsPalindrome(11));
  printf("93433439 is a palindrome: %d\n", MathUtil::IsPalindrome(93433439));
  printf("2134 is not a palindrome: %d\n", MathUtil::IsPalindrome(2134));
}

void testgcd()
{
  unsigned int a, b;
  a = 1071, b= 462;
  printf("gcd(%d, %d) is 21: %d\n", a, b, MathUtil::GCD(a,b));
}

void testSumOfMultiplesBelow()
{
  printf("sumofmulitplesbelow 20 of 3 is 63: %d\n", MathUtil::SumOfMultiplesBelow(20, 3));
}

void testlcm()
{
  unsigned int a, b;
  a = 21, b = 6;
  printf("lcm(%d, %d) is 42: %d\n", a, b, MathUtil::LCM(a, b));
}

void testIsSquare()
{
  unsigned int n = 4;
  printf("%d is square: %d\n", n, MathUtil::IsSquare(n));
  n = 500;
  printf("%d is square: %d\n", n, MathUtil::IsSquare(n));
}

void testLESqrt()
{
  unsigned int n[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  unsigned int i = 0;
  for (i = 0; i < 9; i++){
    printf("%d is the lesqrt: %d\n", MathUtil::LESqrt(n[i]), n[i]);  
  }
}

void testModPower()
{
  unsigned long a, n, m;
  a = 10;
  n = 10;
  m = 10000000000;
  printf("a=%lu, n=%lu, m=%lu: %lu\n", a, n, m, MathUtil::ModPower(a, n, m));
}

void testSumOfDivisors()
{
  unsigned int i;
  for (i = 1; i < 1000; i++)
    printf("n=%d, sum of divisors is: %d\n", i, MathUtil::SumOfDivisors(i));
}

int main()
{
  testSumOfMultiplesBelow();
  testIsPalindrome();
  testgcd();
  testlcm();
  testIsSquare();
  testLESqrt();
  testModPower();
  testSumOfDivisors();

  return 0;
}
