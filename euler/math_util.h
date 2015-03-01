#ifndef _MATH_UTIL_H
#define _MATH_UTIL_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

class MathUtil{
 public:
  static int SumOfMultiplesBelow(int n, int factor);

  static bool IsPalindrome(unsigned int n);

  static bool IsPalindromeWithBase(unsigned int n, unsigned int base);

  static unsigned int GreatestCommonFactor(unsigned int a, unsigned int b);

  static unsigned int GCD(unsigned int a, unsigned int b);

  static unsigned int LeastCommonMultiple(unsigned int a, unsigned int b);

  static unsigned int LCM(unsigned int a, unsigned int b);

  static unsigned int SumOfSquare(unsigned int n);

  static unsigned int SumOfLinear(unsigned int n);

  static unsigned int IsPrime(unsigned int n);

  static bool IsSquare(unsigned int n);

  static unsigned int LESqrt(unsigned int n);

  static unsigned long ModMultiple(unsigned long a, unsigned long b, unsigned long m);

  static unsigned long ModAdd(unsigned long a, unsigned long b, unsigned long m);

  static unsigned long ModPower(unsigned long a, unsigned long n, unsigned long m);

  static unsigned int SumOfDivisors(unsigned int n);

  static bool CompareExponentialNumber(double base1, double exp1, double base2, double exp2);

  static void ExtendedEuclideanAlgorithm(int a, int b, int* gcd, int* s, int* t);

  static int ESieve(int limit, int primes[], int length);
};

/*
  http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 */
int MathUtil::ESieve(int limit, int primes[], int length)
{
  bool tags[limit + 1];
  int i, j;
  int currentPrime;
  int count = 0;
  // assume all the numbers are primes
  for (i=2; i < limit; i++) tags[i] = true;

  int sqrt = LESqrt(limit);
  i = 2;
  while (i <= sqrt){
    // find the next prime
    while (tags[i] == false) i++;
    currentPrime = i;
    i++;//forward for next lookup

    if (length <= count) return length;
    // store the prime
    primes[count++] = currentPrime;

    // set the numbers {n^2, n^2+n, n^2 + 2*n, ..., n^2+k*n(<=limit)} to be non-prime
    j = currentPrime * currentPrime;
    while (j <= limit) {
      tags[j] = false;
      j += currentPrime;
    }
  }
  // store the remain primes to array primes
  while (i <= limit){
    if (tags[i]){
      if (length <= count) return length;
      primes[count++] = i;
    }
    i++;
  }
  return count;
}

bool MathUtil::CompareExponentialNumber(double base1, double exp1, double base2, double exp2)
{
  return exp1*log(base1) > exp2 * log(base2);
}

/*
  http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm;
  http://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity;

  assume a > b;
  r0 = a, r1 = b;
  r_(i+1) = r_(i-1) - q_i * r_i, 0 <= r_(i+1) < r_i;
  
  a * s_i + b * t_i = r_i; define s_i, t_i to keep the equation
  s_0 = 1, t_0 = 0;
  s_1 = 0, t_1 = 1; so when i = 0,1, the equation is keeping

  to keep the equation hold when i > 1, we should have:
  a * s_(i+1) + b * t_(i+1) = a * s_(i-1) + b * t_(i-1) - q_i * (a * s_i + b * t_i);
  then, we could have:
  s_(i+1) = s_(i-1) - q_i * s_i;
  t_(i+1) = t_(i-1) - q_i * t_i;

  when r_(k+1) = 0, r_(k-1) = q_k * r_k; gcd(r0, r1) = gcd(r_k, r_(k-1)) = r_k
  and a * s_k + b * t_k = r_k = gcd(r_k, r_(k-1))
 */
void MathUtil::ExtendedEuclideanAlgorithm(int a, int b, int* gcd, int* s, int* t)
{
  int rPrevious = a, rCurrent = b, rNext;
  int sPrevious = 1, sCurrent = 0, sNext;
  int tPrevious = 0, tCurrent = 1, tNext;
  int q;

  if (a < b){
    rPrevious = b;
    rCurrent = a;
  }
  do{
    q = rPrevious / rCurrent;
    rNext = rPrevious - q * rCurrent;

    sNext = sPrevious - q * sCurrent;
    tNext = tPrevious - q * tCurrent;

    rPrevious = rCurrent;
    rCurrent = rNext;

    sPrevious = sCurrent;
    sCurrent = sNext;

    tPrevious = tCurrent;
    tCurrent = tNext;
  }while (rNext > 0);

  *gcd = rPrevious;
  *s = sPrevious;
  *t = tPrevious;
}

int MathUtil::SumOfMultiplesBelow(int n, int factor)
{
  if (n <= factor) return 0;
  int k = (n - 1) / factor;
  return factor * k * (k + 1) / 2;
}

// if n is one digit, then this function will return true
// this is equal to IsPalindromeWithBase(n, 10);
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

bool MathUtil::IsPalindromeWithBase(unsigned int n, unsigned int base)
{
  unsigned int pbase = 1;
  unsigned int baseSquare = base * base;
  while (n / pbase > base -1) pbase *= base;
  while (n > 0){
    unsigned int left = n / pbase;
    unsigned int right = n % base;
    if (left != right) return false;
    n = (n % pbase) / base;
    pbase /= baseSquare;
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

/*
sqrt(n) <= n/2 + 1;
 */
unsigned int MathUtil::LESqrt(unsigned int n)
{
  unsigned int low = 1, high = n/2 + 2;
  unsigned int middle;
  /*
    let sqrt of n is sqrt, LESqrt of n is lesqrt;
    sqrt must be in [low, high)
    lesqrt <= sqrt < lesqrt + 1;
   */
  while (low < high){
    // low <= middle < high
    middle = low + (high - low)/2;
    if (middle <= n/middle && (middle + 1) > n/(middle + 1)) return middle;
    // sqrt < middle 
    // sqrt must be [low, high)
    else if (middle > n/middle) high = middle;
    // middle +1 <= sqrt
    // sqrt must be in [low, high)
    else low = middle + 1;
    // [low, high) is reducing
  }
  return low;
}

/*
  (a+b) % m = (a%m + b%m)%m;
 */
unsigned long MathUtil::ModAdd(unsigned long a, unsigned long b, unsigned long m)
{
  return (a %m + b %m)%m;
}

/*
  (a*b) %m = ((a%m)*(b%m)) %m
 */
unsigned long MathUtil::ModMultiple(unsigned long a, unsigned long b, unsigned long m)
{
  return ((a%m) * (b%m))%m;
}

unsigned long MathUtil::ModPower(unsigned long a, unsigned long n, unsigned long m)
{
  if (n == 0) return 1;
  if (n == 1) return a % m;
  unsigned long p;
  if (n % 2 == 1){
    p = ModPower(a, (n-1)/2, m);
    // (p*p)%m may be overflow
    return ((a%m)*((p*p)%m))%m;
  }else{
    p = ModPower(a, n/2, m);
    return (p*p) % m;
  }
}

/*
  A = a_1^(n_1) * a_2^(n_2) * a_3^(n_3) * a_4^(n_4) * ... * a_k^(n_k);
  2 <= a_1 < a_2 < a_3 < a_4 < a_k, are primes
  0 <= n_1, n_2, n_3, n_4, ..., n_k, n_k >= 1;
  sum = (a_1^0 + a_1^1 + a_1^2 + ... + a_1^(n_1))*
        (a_2^0 + a_2^1 + a_2^2 + ... + a_2^(n_2))*
        (a_3^0 + a_3^1 + a_3^2 + ... + a_3^(n_3))*
        ...
        (a_k^0 + a_k^1 + a_k^2 + ... + a_k^(n_k))
        - A;

  a^0 + a^1 + a^2 + ... + a^n = (a^(n+1) - 1)/(a - 1);
  if n == 0, then (a-1)/(a-1) = 1, which will not affect the final result

  TODO: this algorithm should be optimized
*/
unsigned int MathUtil::SumOfDivisors(unsigned int n)
{
  unsigned int sum = 1;
  unsigned int remain = n;
  unsigned int factor = 2;
  unsigned int partialSum = factor;

  if (n <= 0) return 0;
  while (remain != 1){
    if (remain % factor == 0){
      // factor must be prime
      // factor must be a_1, a_2, a_3, a_4, ..., a_k orderly;
      partialSum *= factor;
      remain /= factor;
    }else{
      // another factor. this factor may not be prime
      sum *= (partialSum - 1)/(factor - 1);
      factor = (factor == 2)? 3 : (factor + 2);
      partialSum = factor;
    }
  }
  if (remain == 1)
    sum *= (partialSum - 1)/(factor - 1);
  // exclusive itself according to the definition
  sum -= n;
  return sum;
}

#endif
