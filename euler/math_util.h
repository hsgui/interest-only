#ifndef _MATH_UTIL_H
#define _MATH_UTIL_H

#include<stdio.h>
#include<stdlib.h>

class MathUtil{
 public:
  static int SumOfMultiplesBelow(int n, int factor);

  static bool IsPalindrome(unsigned int n);
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
#endif
