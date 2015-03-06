#include<stdio.h>
#include<stdlib.h>

#include "big_integer.h"

int PowerfulDigitSum_56(int a, int b)
{
  int length = 202;
  int digits[length], resultd[length];
  BigInteger biga(digits, length);
  BigInteger result(resultd, length);
  BigInteger::ConvertIntToBigInteger(a, biga);
  BigInteger::ConvertIntToBigInteger(0, result);
  for (int i = 1; i < b; i++){
    int j = a;
    // try to compute sum_{i=1..a}(biga); where biga = a^i;
    while (j > 0){
      if ((j & 1) != 0){
        BigInteger::Add(result, biga);
      }
      j = j>>1;
      BigInteger::Add(biga, biga);
    }
    // result = a^(i+1);
    // biga = result
    // result = 0 to compute a*biga if needed
    BigInteger::CopyTo(result, biga);
    BigInteger::ConvertIntToBigInteger(0, result);
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
