#include<stdio.h>
#include<stdlib.h>

struct BigInteger
{
  int sdcount;
  int length;
  int* digits;
};

typedef struct BigInteger BigInteger;

void ConvertIntToBigInteger(int n, BigInteger& bi)
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

void Trim(BigInteger& a)
{
  while (a.sdcount >= 1 && a.digits[a.sdcount-1] == 0){
    a.sdcount--;
  }
}

bool LessThan(BigInteger& a, BigInteger& b)
{
  Trim(a);
  Trim(b);
  if (a.sdcount < b.sdcount) return true;
  if (a.sdcount > b.sdcount) return false;
  int i;
  for (i = a.sdcount -1; i >= 0; i--){
    if (a.digits[i] > b.digits[i]) return false;
    if (a.digits[i] < b.digits[i]) return true;
  }
}

void MultiplePower10(BigInteger& a, int power){
  if (a.sdcount + power > a.length) return;
  int i;
  for (i = a.sdcount + power - 1; i >= power; i--){
    a.digits[i] = a.digits[i-power];
  }
  for (i=0; i < power; i++){
    a.digits[i] = 0;
  }
  a.sdcount += power;
}

void DividePower10(BigInteger& a, int power){
  int i;
  for (i = 0; i < a.sdcount - power; i++){
    a.digits[i] = a.digits[i+power];
  }
  a.sdcount -= power;
}

void AddOneDigit(BigInteger& a, int digit, int pos)
{
  int i;
  for (i = a.sdcount; i>=pos; i--){
    a.digits[i] = a.digits[i-1];
  }
  a.digits[pos-1] = digit;
  a.sdcount++;
}

void Add(BigInteger& a, BigInteger& b)
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
void Minus(BigInteger& a, BigInteger& b)
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

int CountDigitSum(BigInteger& a)
{
  int i;
  int sum = 0;
  for (i = 0; i < a.sdcount; i++){
    sum += a.digits[i];
  }
  return sum;
}

void PrintBigInteger(BigInteger& a){
  int i;
  bool ignoreZero = true;
  for (i = a.sdcount-1; i >= 0; i--){
    if (ignoreZero && a.digits[i] != 0){
      ignoreZero = false;
    }
    if (!ignoreZero){
      printf("%d",a.digits[i]);
    }
  }
  printf("\n");
}

/*
  http://www.afjarvis.staff.shef.ac.uk/maths/jarvisspec02.pdf
 */
int SquareRootDigitExpansion_80(int n, int digit)
{
  int digitCount = digit + 2;
  BigInteger limit;
  int limits[digitCount];
  int i;
  for (i = 0; i < digitCount; i++) limits[i] = 0;
  limits[digitCount-1] = 1;
  limit.digits = limits, limit.length = digitCount, limit.sdcount = digitCount;

  BigInteger ten;
  int tend[digitCount];
  ten.digits = tend, ten.length = digitCount;
  ConvertIntToBigInteger(10, ten);

  BigInteger a;
  int as[digitCount];
  a.digits = as, a.length = digitCount, a.sdcount = 0;

  BigInteger b;
  int bs[digitCount];
  b.digits = bs, b.length = digitCount, b.sdcount = 0;

  ConvertIntToBigInteger(5*n, a);
  ConvertIntToBigInteger(5, b);

  while (LessThan(b, limit)){
    if (LessThan(a, b)){
      MultiplePower10(a, 2);
      AddOneDigit(b, 0, 2);
    }else{
      Minus(a, b);
      Add(b, ten);
    }
  }

  DividePower10(b, 2);
  return CountDigitSum(b);
}

void test()
{
  BigInteger a, b;
  int digits1[100], digits2[100];
  a.length = 100, b.length = 100;
  a.digits = digits1, b.digits = digits2;
  
  a.digits[0] = 9, a.digits[1]=9;
  a.sdcount = 2;

  b.digits[0] = 1, b.digits[1] = 1, b.digits[2] = 8;
  b.sdcount = 3;

  Add(a, b);
  PrintBigInteger(a);
  Minus(a, b);
  PrintBigInteger(a);

  AddOneDigit(a, 0, 2);
  PrintBigInteger(a);
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
  //test();
}
