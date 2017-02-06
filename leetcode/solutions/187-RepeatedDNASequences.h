#pragma once

#include <unordered_map>
#include <cassert>

using namespace std;

class RepeatedDNASequences
{
public:
    vector<string> findRepeatedDnaSequences(string s)
    {
        vector<string> sequences;
        if (s.length() <= 10)
        {
            return sequences;
        }

        const int windowSize = 10;
        char coding[26];
        coding['A' - 'A'] = 0;
        coding['C' - 'A'] = 1;
        coding['G' - 'A'] = 2;
        coding['T' - 'A'] = 3;

        char decoding[4];
        decoding[0] = 'A';
        decoding[1] = 'C';
        decoding[2] = 'G';
        decoding[3] = 'T';

        int code = 0;
        for (int i = 0; i < windowSize; i++)
        {
            code = (code << 2) | coding[s[i] - 'A'];
        }

        unordered_map<int, int> codeToCount;
        codeToCount[code] = codeToCount[code] + 1;
        for (int index = windowSize; index < s.length(); index++)
        {
            code = ((code << 2) & 0xfffff) | coding[s[index] - 'A'];
            codeToCount[code] = codeToCount[code] + 1;
        }

        char decode[windowSize + 1];
        for (auto pair : codeToCount)
        {
            if (pair.second > 1)
            {
                code = pair.first;
                decode[windowSize] = '\0';
                for (int index = windowSize - 1; index >= 0; index--)
                {
                    decode[index] = decoding[(code & 3)];
                    code = code >> 2;
                }
                sequences.push_back(decode);
            }
        }

        return sequences;
    }

    bool Test()
    {
        string c1 = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        vector<string> result = findRepeatedDnaSequences(c1);
        vector<string> expected = { "AAAAACCCCC", "CCCCCAAAAA" };
        assert(result == expected);

        return true;
    }
};