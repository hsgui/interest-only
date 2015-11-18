#include <algorithm>
#include <vector>
#include <memory>
#include <array>
#include <unordered_map>
#include <cassert>

using namespace std;

class LongestPalindromicSubstring
{
public:
    string longestPalindrome(string s)
    {
        const int maxLength = 1000;
        int length = s.length();
        bool isPalindrome[maxLength][maxLength] = { false };

        int maxPalindromeLength = 0;
        int palindromeStart = 0;
        for (int i = 0; i < length; i++)
        {
            isPalindrome[i][i] = true;
            maxPalindromeLength = 1;
        }
        for (int i = 0; i < length - 1; i++)
        {
            if (s[i] == s[i + 1])
            {
                isPalindrome[i][i + 1] = true;
                maxPalindromeLength = 2;
                palindromeStart = i;
            }
        }
        for (int len = 3; len <= length; len++)
        {
            for (int i = 0; i < length - len + 1; i++)
            {
                int j = i + len - 1;
                if (s[i] == s[j] && isPalindrome[i + 1][j - 1])
                {
                    isPalindrome[i][j] = true;
                    maxPalindromeLength = len;
                    palindromeStart = i;
                }
            }
        }

        return s.substr(palindromeStart, maxPalindromeLength);
    }

    // optimize the memory usage to O(n)
    string longestPalindromeV2(string s)
    {
        const int maxLength = 1000;
        int length = s.length();
        int palindromeLength[maxLength] = { 0 };

        int maxPalindromeLength = 0;
        int palindromeStart = 0;
        for (int i = 0; i < length; i++)
        {
            palindromeLength[i] = 1;
            maxPalindromeLength = 1;
        }
        for (int i = 0; i < length - 1; i++)
        {
            if (s[i] == s[i + 1])
            {
                palindromeLength[i] = 2;
                maxPalindromeLength = 2;
                palindromeStart = i;
            }
        }
        for (int len = 3; len <= length; len++)
        {
            for (int i = 0; i < length - len + 1; i++)
            {
                int j = i + len - 1;
                if (s[i] == s[j] && palindromeLength[i+1] == len - 2)
                {
                    palindromeLength[i] = len;
                    maxPalindromeLength = len;
                    palindromeStart = i;
                }
            }
        }

        return s.substr(palindromeStart, maxPalindromeLength);
    }

    // no additional memory required
    string longestPalindromeV3(string s)
    {
        int maxPalindromeLength = 0;
        tuple<int, int> maxRange;
        for (int i = 0; i < s.length(); i++)
        {
            tuple<int, int> range = expandAroundCenter(s, i, i);
            if (get<1>(range) -get<0>(range) +1 > maxPalindromeLength)
            {
                maxPalindromeLength = get<1>(range) -get<0>(range) +1;
                maxRange = range;
            }
            range = expandAroundCenter(s, i, i + 1);
            if (get<1>(range) -get<0>(range) +1 > maxPalindromeLength)
            {
                maxPalindromeLength = get<1>(range) -get<0>(range) +1;
                maxRange = range;
            }
        }
        return s.substr(get<0>(maxRange), maxPalindromeLength);
    }

    tuple<int, int> expandAroundCenter(const string& s, int c1, int c2)
    {
        int left = c1, right = c2;
        int length = s.length();
        for (; left >= 0 && right < length && s[left] == s[right]; --left, ++right);
        tuple<int, int> range(left + 1, right - 1);
        return range;
    }

    bool Test()
    {
        unordered_map<string, string> testCases;
        testCases.insert({ "a", "a" });
        testCases.insert({ "abac", "aba" });
        testCases.insert({ "ababa", "ababa" });
        unordered_map<string, string>::iterator it;
        for (it = testCases.begin(); it != testCases.end(); ++it)
        {
            assert((longestPalindromeV3(it->first)).compare(it->second) == 0);
        }

        return true;
    }
};