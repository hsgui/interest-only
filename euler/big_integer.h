#ifndef _BIG_INTEGER_H_
#define _BIG_INTEGER_H_

#include<stdio.h>
#include<stdlib.h>

class BigInteger{
 public:
  BigInteger(int* digits, int length);
  
  BigInteger(int* digits, int length, int sdcount);

  void static ConvertIntToBigInteger(int n, BigInteger& bi);

  void static Trim(BigInteger& a);

  bool static LessThan(BigInteger& a, BigInteger& b);

  void static MultiplePower10(BigInteger& a, int power);

  void static DividePower10(BigInteger& a, int power);

  void static AddOneDigit(BigInteger& a, int digit, int pos);

  void static Add(BigInteger& a, BigInteger& b);

  void static Minus(BigInteger& a, BigInteger& b);

  int static CountDigitSum(BigInteger& a);

  void static PrintBigInteger(BigInteger& a);

 private:
  void Init(int* digitsArg, int lengthArg, int sdcountArg);

  int sdcount;
  int length;
  int* digits;
};

BigInteger::BigInteger(int* digitsArg, int lengthArg)
{
  Init(digitsArg, lengthArg, 0);
}

BigInteger::BigInteger(int* digits, int length, int sdcount)
{
  Init(digits, length, sdcount);
}

void BigInteger::Init(int* digitsArg, int lengthArg, int sdcountArg)
{
  sdcount = sdcountArg;
  length = lengthArg;
  digits = digitsArg;
}

void BigInteger::ConvertIntToBigInteger(int n, BigInteger& bi)
{
  int count = 0;

  while (n > 0 && count < bi.length){
    int digit = n % 10;
    bi.digits[count++] = digit;
    n /= 10;
  }
  if (n > 0 && count >= bi.length){
    printf("the array is too small\n");
  }
  bi.sdcount = count;
}

void BigInteger::Trim(BigInteger& a)
{
  while (a.sdcount >= 1 && a.digits[a.sdcount-1] == 0){
    a.sdcount--;
  }
}

bool BigInteger::LessThan(BigInteger& a, BigInteger& b)
{
  Trim(a);
  Trim(b);
  if (a.sdcount < b.sdcount) return true;
  if (a.sdcount > b.sdcount) return false;
  
  for (int i = a.sdcount -1; i >= 0; i--){
    if (a.digits[i] > b.digits[i]) return false;
    if (a.digits[i] < b.digits[i]) return true;
  }
}

void BigInteger::MultiplePower10(BigInteger& a, int power){
  if (a.sdcount + power > a.length) return;
  
  for (int i = a.sdcount + power - 1; i >= power; i--){
    a.digits[i] = a.digits[i-power];
  }
  for (int i=0; i < power; i++){
    a.digits[i] = 0;
  }
  a.sdcount += power;
}

void BigInteger::DividePower10(BigInteger& a, int power){
  for (int i = 0; i < a.sdcount - power; i++){
    a.digits[i] = a.digits[i+power];
  }
  a.sdcount -= power;
}

void BigInteger::AddOneDigit(BigInteger& a, int digit, int pos)
{
  for (int i = a.sdcount; i>=pos; i--){
    a.digits[i] = a.digits[i-1];
  }
  a.digits[pos-1] = digit;
  a.sdcount++;
}

void BigInteger::Add(BigInteger& a, BigInteger& b)
{
  int sd = 0;
  int carry = 0;
  int max = (a.sdcount > b.sdcount) ? a.sdcount : b.sdcount;
  while (sd < max){
    int sum = carry;
    if (sd < a.sdcount){
      sum += a.digits[sd];
    }
    if (sd < b.sdcount){
      sum += b.digits[sd];
    }

    carry = sum / 10;
    a.digits[sd] = sum % 10;
    if (sd >= a.sdcount){
      a.sdcount++;
    }
    sd++;
  }
  if (carry > 0){
    a.digits[a.sdcount++] = carry;
  }
}

// a>=b
void BigInteger::Minus(BigInteger& a, BigInteger& b)
{
  int sd = 0;
  int carry = 0;
  while (sd < a.sdcount){
    int sum = a.digits[sd] - carry;
    if (sd < b.sdcount){
      sum -= b.digits[sd];
    }
    if (sum < 0){
      carry = 1;
      sum += 10;
    }else{
      carry = 0;
    }
    a.digits[sd] = sum;
    sd++;
  }
}

int BigInteger::CountDigitSum(BigInteger& a)
{
  int sum = 0;
  for (int i = 0; i < a.sdcount; i++){
    sum += a.digits[i];
  }
  return sum;
}

void BigInteger::PrintBigInteger(BigInteger& a){
  bool ignoreZero = true;
  for (int i = a.sdcount-1; i >= 0; i--){
    if (ignoreZero && a.digits[i] != 0){
      ignoreZero = false;
    }
    if (!ignoreZero){
      printf("%d",a.digits[i]);
    }
  }
  printf("\n");
}

#endif
