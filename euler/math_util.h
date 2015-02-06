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

  static unsigned int SumOfSquare(unsigned int n);

  static unsigned int SumOfLinear(unsigned int n);

  static unsigned int IsPrime(unsigned int n);

  static bool IsSquare(unsigned int n);
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

// 1^2 + 2^2 + 3^2 + 4^2 + ... + n^2 = (n(n+1)(2*n +1))/6
// 1. we could make an assumption that it = a*n^3 + b*n^2 + c*n + d
// 2. mathforum.org/library/drmath/view/56920.html
unsigned int MathUtil::SumOfSquare(unsigned int n)
{
  return (n*(n+1)*(n+n+1))/6;
}

unsigned int MathUtil::SumOfLinear(unsigned int n)
{
  return n*(n+1)/2;
}

unsigned int MathUtil::IsPrime(unsigned int n)
{
  if (1 == n) return false;
  if (2 == n || 3 == n) return true;
  if (n % 2 == 0) return false;
  unsigned int factor = 3;
  while (factor * factor <= n){
    if (n % factor == 0) return false;
    factor += 2;
  }
  return true;
}

bool MathUtil::IsSquare(unsigned int n)
{
  unsigned int remain = n;
  unsigned int factor = 2;
  
  unsigned int square = factor * factor;
  while (square <= remain){
    if (remain % factor == 0){
      if (remain % square != 0) return false;
      remain /= square;
    }else{
      factor = (factor == 2) ? 3 : (factor + 2);
      square = factor * factor;
    }
  }
  return remain == 1;
}

#endif
