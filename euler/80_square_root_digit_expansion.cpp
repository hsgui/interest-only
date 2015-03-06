#include<stdio.h>
#include<stdlib.h>

#include "big_integer.h"

/*
  http://www.afjarvis.staff.shef.ac.uk/maths/jarvisspec02.pdf
 */
int SquareRootDigitExpansion_80(int n, int digit)
{
  int digitCount = digit + 2;
  int limits[digitCount];

  for (int i = 0; i < digitCount; i++) limits[i] = 0;
  limits[digitCount-1] = 1;

  BigInteger limit(limits, digitCount, digitCount);

  int tend[digitCount];
  BigInteger ten(tend, digitCount);
  BigInteger::ConvertIntToBigInteger(10, ten);

  int as[digitCount];
  BigInteger a(as, digitCount);

  int bs[digitCount];
  BigInteger b(bs, digitCount);

  BigInteger::ConvertIntToBigInteger(5*n, a);
  BigInteger::ConvertIntToBigInteger(5, b);

  while (BigInteger::LessThan(b, limit)){
    if (BigInteger::LessThan(a, b)){
      BigInteger::MultiplePower10(a, 2);
      BigInteger::AddOneDigit(b, 0, 2);
    }else{
      BigInteger::Minus(a, b);
      BigInteger::Add(b, ten);
    }
  }

  BigInteger::DividePower10(b, 2);
  return BigInteger::CountDigitSum(b);
}

int main()
{
  int result = 0;
  int j = 1, i;
  for (i = 1; i <= 100; i++){
    if (j*j == i){
      j++;
      continue;
    }
    result += SquareRootDigitExpansion_80(i, 100);
  }
  printf("%d\n", result);
}
