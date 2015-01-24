#include<stdio.h>
#include<stdlib.h>

#include "skiplist.h"

typedef int Key;

struct Comparator {
  int operator()(const Key& a, const Key&b) const{
    if (a < b){
      return -1;
    }else if (a > b){
      return +1;
    }else{
      return 0;
    }
  }
};

int main()
{
  Comparator cmp;
  algorithms::SkipList<Key, Comparator> list(cmp);
  list.Insert(4);
  list.Insert(2);
  list.Insert(9);
  list.Insert(6);
  list.Insert(1);
  list.Insert(23);
  list.Insert(12);
  list.Insert(35);
  list.Insert(10);

  printf("initial list\n");
  list.PrettyPrintList();

  bool is = list.Contains(5);
  printf("list contains 5, %d\n", is);
  is = list.Contains(6);
  printf("list contains 6, %d\n", is);
}
