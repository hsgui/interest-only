#pragma once

#include <unordered_map>
#include <cassert>
#include <algorithm>

using namespace std;

class MaximumProductOfWordLengths
{
public:
    int maxProduct(vector<string>& words)
    {
        unordered_map<int, int> maxlen;
        for (auto& word : words)
        {
            int mask = 0;
            for (auto ch : word)
            {
                mask |= (1 << (ch - 'a'));
            }
            if (mask == 0) continue;

            maxlen[mask] = max(maxlen[mask], (int)word.length());
        }

        int result = 0;
        for (auto a : maxlen)
            for (auto b : maxlen)
            {
                if ((a.first & b.first) == 0)
                {
                    result = max(result, a.second * b.second);
                }
            }

        return result;
    }

    bool Test()
    {
        vector<string> c1 = { "a", "aa", "aaa", "aaaa" };
        int result = maxProduct(c1);
        assert(result == 0);

        vector<string> c2 = { "a", "ab", "abc", "d", "cd", "bcd", "abcd" };
        result = maxProduct(c2);
        assert(result == 4);

        vector<string> c3 = { "abcw", "baz", "foo", "bar", "xtfn", "abcdef" };
        result = maxProduct(c3);
        assert(result == 16);

        return true;
    }
};