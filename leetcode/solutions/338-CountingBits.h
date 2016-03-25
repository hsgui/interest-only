#pragma once

#include <vector>
// https://leetcode.com/problems/counting-bits/
class CountingBits
{
public:
    std::vector<int> countBits(int num)
    {
        std::vector<int> counts;
        counts.reserve(num + 1);
        if (num >= 0)
        {
            counts.push_back(0);
        }
        for (int i = 1; i <= num; ++i)
        {
            counts.push_back(counts[(i - 1) & i] + 1);
        }

        return counts;
    }
};