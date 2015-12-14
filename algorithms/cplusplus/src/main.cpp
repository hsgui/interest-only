#include <iostream>
#include "skiplist_test.h"
#include "graph_test.h"

using namespace UnitTest;
int main()
{
    SkipListUnitTest::test();
    GraphUnitTest::test();

    system("pause");

    return 0;
}