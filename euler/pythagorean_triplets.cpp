#include<stdio.h>
#include<stdlib.h>

#include "math_util.h"

/*
a + b + c = sum;
c > b > a;
a^2 + b^2 = c^2 => c < a + b;
sum = a + b + c < c + c + c => c > sum /3;
sum = a + b + c > c + c => c < sum/2;
a + b = sum - c < b + b => b > (sum - c)/2;
 */
void PythagoreanTripletsTrival(unsigned int sum)
{
  unsigned int a, b, c;
  for (c = sum / 3 + 1; c < sum / 2; c++){
    for (b = (sum - c) / 2 + 1; b < c; b++){
      a = sum - b - c;
      // be careful of overflow
      if ((unsigned long)a*a + (unsigned long)b*b == (unsigned long)c*c){
        printf("a=%d, b=%d, c=%d, sum=%d\n", a, b, c, sum); 
      }
    }
  }
}

/*
all primitive pythagorean triplets can be represented as:
a = m^2 - n^2, b = 2*m*n, c = m^2 + n^2;
when sum is large, it's very effective
 */
void PythagoreanTriplets(unsigned int sum)
{
  unsigned int a, b, c;
  unsigned int sumDiv2 = sum / 2;
  unsigned int mMax = MathUtil::LESqrt(sumDiv2);
  unsigned int m, n, k, d;
  unsigned int mnd;
  for (m = 2; m <= mMax; m++){
    if (sumDiv2 % m == 0){
      mnd = sumDiv2 / m;
      while (mnd %2 == 0) mnd /= 2;
      k = (m % 2 == 1) ? (m + 2) : (m+1);
      while (k < 2*m && k < mnd){
        if (mnd % k == 0 && MathUtil::GCD(k, m) == 1){
          n = k - m;
          d = sumDiv2 / (k * m);
          a = (m*m - n*n)*d;
          b = 2*m*n*d;
          c = (m*m + n*n)*d;
          printf("a=%d, b=%d, c=%d, sum=%d\n", a, b, c, sum);
        }
        k += 2;
      }
    }
  }
}
int main()
{
  PythagoreanTripletsTrival(1000);
  PythagoreanTriplets(1000);

  printf("PythagoreanTripletsTrival\n");
  PythagoreanTripletsTrival(1000000);
  printf("PythagoreanTriplets\n");
  PythagoreanTriplets(1000000);
}
