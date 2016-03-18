#pragma once

#include "hamt.h"

namespace UnitTest
{
    namespace HAMTTest
    {
        using namespace algorithms;

        void testUsage()
        {
            HAMT<unsigned, unsigned> map;
            map.set(23, 21);
            auto value = map.find(23);
            std::cout << *value << std::endl;
        }
        void test()
        {
            testUsage();
        }
    }
}