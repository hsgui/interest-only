#include<stdio.h>
#include<stdlib.h>

#include "big_integer.h"

int PowerfulDigitSum_56(int a, int b)
{
  int length = 202;
  int digits[length];
  BigInteger biga(digits, length);

  BigInteger::ConvertIntToBigInteger(a, biga);

  for (int i = 1; i < b; i++){
    BigInteger::MultipleInt(biga, a);
  }

  return BigInteger::CountDigitSum(biga);
}

int main()
{
  int max = 1;

  for (int a = 2; a < 100; a++)
    for (int b = 1; b < 100; b++){
      int sum = PowerfulDigitSum_56(a, b);
      if (max < sum) max = sum;
    }
  printf("%d\n", max);
}
