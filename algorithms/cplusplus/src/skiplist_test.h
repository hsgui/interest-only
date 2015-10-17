#include<stdio.h>
#include<stdlib.h>

#include "skiplist.h"

namespace UnitTest
{
	class SkipListUnitTest
	{
		typedef int Key;
		struct Comparator {
			int operator()(const Key& a, const Key&b) const {
				if (a < b) {
					return -1;
				}
				else if (a > b) {
					return +1;
				}
				else {
					return 0;
				}
			}
		};

	public:
		static int test()
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

			is = list.Delete(10);
			printf("list delete 10, %d\n", is);

			is = list.Delete(100);
			printf("list delete 100, %d\n", is);

			is = list.Delete(3);
			printf("list delete 3, %d\n", is);

			list.PrettyPrintList();

			return 0;
		}
	};
}
