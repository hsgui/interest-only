#pragma once

#include <algorithm>
#include <cassert>
using namespace std;

class BulbSwitcher
{
public:
    int bulbSwitch(int n) {
        if (n == 0)
        {
            return 0;
        }
        // sqrt(n) <= n / 2 + 1;
        unsigned int low = 1, high = n / 2 + 2;
        unsigned int middle;
        /*
        let sqrt of n is sqrt, LESqrt of n is lesqrt;
        sqrt must be in [low, high)
        lesqrt <= sqrt < lesqrt + 1;
        */
        while (low < high) {
            // low <= middle < high
            middle = low + (high - low) / 2;
            if (middle <= n / middle && (middle + 1) > n / (middle + 1)) return middle;
            // sqrt < middle 
            // sqrt must be [low, high)
            else if (middle > n / middle) high = middle;
            // middle +1 <= sqrt
            // sqrt must be in [low, high)
            else low = middle + 1;
            // [low, high) is reducing
        }
        return low;
    }

    bool Test()
    {
        assert(bulbSwitch(0) == 0);
        assert(bulbSwitch(1) == 1);
        assert(bulbSwitch(2) == 1);
        assert(bulbSwitch(4) == 2); // 1, 4
        assert(bulbSwitch(5) == 2); // 1, 4

        return true;
    }
};