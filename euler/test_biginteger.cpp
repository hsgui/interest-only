#include<stdio.h>
#include<stdlib.h>

#include "big_integer.h"

void test()
{
  int length = 100;
  int digits1[length], digits2[length];
  BigInteger a(digits1, length);
  BigInteger b(digits2, length);
  
  BigInteger::ConvertIntToBigInteger(811, a);
  BigInteger::ConvertIntToBigInteger(99, b);

  BigInteger::Add(a, b);
  BigInteger::PrintBigInteger(a);
  BigInteger::Minus(a, b);
  BigInteger::PrintBigInteger(a);

  BigInteger::AddOneDigit(a, 0, 2);
  BigInteger::PrintBigInteger(a);
}

int main()
{
  test();
}
