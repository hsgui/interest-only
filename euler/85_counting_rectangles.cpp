#include<stdio.h>
#include<stdlib.h>

int abs(int a)
{
  return a > 0 ? a : (-a);
}

/*
  for grid n*m, it could contain rectangles: 
  1*1, 1*2, 1*3, ..., 1*m;
  2*1, 2*2, 2*3, ..., 2*m;
  ...
  n*1, n*2, n*3, ..., n*m;
  number(i*j) = (n+1-i)*(m+1-j);
  count = sum_{i, j}((n+1-i)(m+1-j))
        = sum_{i, j}(i*j)
        = sum_i(i)*sum_j(j)
        = n*(n+1)/2*m*(m+1)/2;
  
  or another explanation:
  for any little rectangle, it have two vertical lines and two horizontal lines,
  and could make a one-one mapping between the rectangles and the four lines
  we have (n+1)*n/2 different kinds of two vertical lines selection
  and (m+1)*m/2 different kinds of two horizontal lines selction

  count = n*(n+1)*m*(m+1)/4;
  we can suppose n >= m;
  then, when n = 2000, m = 1, we have:
  count = 2001000;
  so, the largest area is 2001000, n <= 2000;
 */
void CountingRectangles_85()
{
  int target = 2000000;
  int n = 2000, m = 1;
  int error = 1000;
  int cn, cm;
  int closestCount;

  while (n >= m){
    int count = n*(n+1)*m*(m+1)/4;
    if (error >= abs(count - target)){
      error = abs(count - target);
      closestCount = count;
      cn = n;
      cm = m;
    }
    if (count > target){
      n--;
    }else if (count < target){
      m++;
    }else{
      break;
    }
  }
  printf("n=%d, m=%d, area=%d, count=%d\n", cn, cm, cn*cm, closestCount);
}

int main()
{
  CountingRectangles_85();
}
