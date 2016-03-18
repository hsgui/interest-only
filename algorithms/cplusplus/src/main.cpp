#include <iostream>
#include "skiplist_test.h"
#include "graph_test.h"
#include "hamt_test.h"

using namespace UnitTest;
int main()
{
    SkipListUnitTest::test();
    GraphUnitTest::test();
    HAMTTest::test();

    system("pause");

    return 0;
}