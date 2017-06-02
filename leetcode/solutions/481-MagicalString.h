#pragma once

#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

// https://leetcode.com/problems/magical-string/#/description
class MagicString
{
public:
    int magicalString(int n) 
    {
        std::vector<uint8_t> numbers;
        numbers.reserve(10000);

        // the first 2 must be: 1, 2, 2
        numbers.push_back(1);
        numbers.push_back(2);
        numbers.push_back(2);
        
        int current = 2;
        int trackingIndex = 2;
        while (current <= n)
        {
            for (size_t i = 0; i < numbers[trackingIndex]; i++)
            {
                numbers.push_back(3 - numbers[current]);
            }
            current += numbers[trackingIndex];
            trackingIndex++;
        }

        int count = 0;
        for (size_t i = 0; i < n; i++)
        {
            if (numbers[i] == 1)
            {
                count++;
            }
        }

        return count;
    }

    bool Test()
    {
        // S = "1221121221221121122бнбн"
        assert(magicalString(0) == 0);
        assert(magicalString(1) == 1);
        assert(magicalString(2) == 1);
        assert(magicalString(5) == 3);
        assert(magicalString(10) == 5);

        return true;
    }
};
