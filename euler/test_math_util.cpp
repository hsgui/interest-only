#include<stdio.h>
#include<stdlib.h>

#include "math_util.h"

void testIsPalindrome()
{
  printf("3 is a palindrome: %d\n", MathUtil::IsPalindrome(3));
  printf("11 is a palindrome: %d\n", MathUtil::IsPalindrome(11));
  printf("93433439 is a palindrome: %d\n", MathUtil::IsPalindrome(93433439));
  printf("2134 is not a palindrome: %d\n", MathUtil::IsPalindrome(2134));
}
int main()
{
  printf("sumofmulitplesbelow 20 of 3 is: %d\n", MathUtil::SumOfMultiplesBelow(20, 3));
  testIsPalindrome();
  return 0;
}
