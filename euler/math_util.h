#ifndef _MATH_UTIL_H
#define _MATH_UTIL_H

#include<stdio.h>
#include<stdlib.h>

class MathUtil{
 public:
  static int SumOfMultiplesBelow(int n, int factor);

  static bool IsPalindrome(unsigned int n);

  static unsigned int GreatestCommonFactor(unsigned int a, unsigned int b);

  static unsigned int GCD(unsigned int a, unsigned int b);

  static unsigned int LeastCommonMultiple(unsigned int a, unsigned int b);

  static unsigned int LCM(unsigned int a, unsigned int b);
};

int MathUtil::SumOfMultiplesBelow(int n, int factor)
{
  if (n <= factor) return 0;
  int k = (n - 1) / factor;
  return factor * k * (k + 1) / 2;
}

// if n is one digit, then this function will return true
bool MathUtil::IsPalindrome(unsigned int n)
{
  unsigned int p10 = 1;
  while (n / p10 > 9) p10 *= 10;
  while (n > 0){
    unsigned int left = n / p10;
    unsigned int right = n % 10;
    if (left != right) return false;
    n = (n % p10) / 10;
    p10 /= 100;
  }
  return true;
}

// en.wikipedia.org/wiki/Euclidean_algorithm
unsigned int MathUtil::GreatestCommonFactor(unsigned int a, unsigned int b)
{
  unsigned int remainder = a;
  if (a < b) {
    remainder = b;
    b = a;
    a = remainder;
  }
  // assert: a >= b
  while (remainder != 0){
    remainder = a % b;
    a = b;
    b = remainder;
  }
  return a;
}

unsigned int MathUtil::GCD(unsigned int a, unsigned int b)
{
  return GreatestCommonFactor(a, b);
}

// en.wikipedia.org/wiki/Least_common_multiple
unsigned int MathUtil::LeastCommonMultiple(unsigned int a, unsigned int b)
{
  return (a/GCD(a, b)) * b;
}

unsigned int MathUtil::LCM(unsigned int a, unsigned int b)
{
  return LeastCommonMultiple(a, b);
}

#endif
