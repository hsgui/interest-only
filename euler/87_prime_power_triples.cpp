#include<unordered_set>
#include<iostream>
#include "math_util.h"

/*
  https://projecteuler.net/problem=87
 */
void PrimePowerTriples_87()
{
  std::unordered_set<int> numbers;
  int limit = 50000000;
  int maxPrime2 = 7071, maxPrime3 = 369, maxPrime4 = 85;
  int power2Primes[maxPrime2], power3Primes[maxPrime3], power4Primes[maxPrime4];
  int count2, count3 = 0, count4 = 0;
  int i, j, k;

  count2 = MathUtil::ESieve(maxPrime2, power2Primes, maxPrime2);
  for (i = 0; i < count2; i++) {
    int prime = power2Primes[i];
    power2Primes[i] = power2Primes[i] * power2Primes[i];
    if (prime <= maxPrime3) power3Primes[count3++] = power2Primes[i] * prime;
    if (prime <= maxPrime4) power4Primes[count4++] = power2Primes[i] * power2Primes[i];
  }

  for (i = 0; i < count2; i++)
    for (j = 0; j < count3; j++)
      for (k = 0; k < count4; k++){
        int num = power2Primes[i] + power3Primes[j] + power4Primes[k];
        if (num < limit) numbers.insert(num);
      }
  std::cout << numbers.size() << std::endl;
}

/*
  to compile this file, please use the following command:
  gcc 87_prime_power_triples.cpp -lm -std=c++11 -lstdc++
 */
int main()
{
  PrimePowerTriples_87();
}
