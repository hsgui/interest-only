#include<stdio.h>
#include<stdlib.h>

#include "big_integer.h"

void PowerfulDigitSum_56()
{
  int a = 100, b = 100;
  int length = 202;
  int digits[length];
  BigInteger biga(digits, length);

  int max = 0;
  for (int i = 2; i < a; i++){
    BigInteger::ConvertIntToBigInteger(i, biga);
    for (int j = 1; j < b; j++){
      BigInteger::MultipleInt(biga, i);
      int sum = BigInteger::CountDigitSum(biga);
      if (sum > max) max = sum;
    }
  }
  printf("%d\n", max);
}

int main()
{
  PowerfulDigitSum_56();
}
