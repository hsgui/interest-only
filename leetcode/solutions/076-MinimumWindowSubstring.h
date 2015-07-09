#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/minimum-window-substring/
// http://articles.leetcode.com/2010/11/finding-minimum-window-in-s-which.html
class MinimumWindowSubstring
{
public:
	string minWindow(string s, string t) 
	{
		int needToFind[256] = {};
		int hasFound[256] = {};
		int tLen = t.length();

		int count = 0;
		int begin = 0;

		int minWindowLength = INT_MAX;
		int minWindowStart = 0;
		int minWindowEnd = 0;

		for (int i = 0; i < tLen; ++i) needToFind[t[i]]++;
		for (int end = 0; end < s.length(); ++end)
		{
			if (needToFind[s[end]] == 0) continue;
			hasFound[s[end]]++;
			if (hasFound[s[end]] <= needToFind[s[end]]) count++;
			if (count == tLen)
			{
				while (needToFind[s[begin]] == 0 
					|| needToFind[s[begin]] < hasFound[s[begin]])
				{
					if (needToFind[s[begin]] < hasFound[s[begin]])
					{
						hasFound[s[begin]]--;
					}
					begin++;
				}
				if (minWindowLength > end - begin + 1)
				{
					minWindowLength = end - begin + 1;
					minWindowStart = begin;
					minWindowEnd = end;
				}
			}
		}
		if (count == tLen)
		{
			return s.substr(minWindowStart, minWindowLength);
		}
		return "";
	}

	bool Test()
	{
		string s = "ADOBECODEBANC";
		string t = "ABC";
		assert(minWindow(s, t) == "BANC");

		s = "abc";
		t = "c";
		assert(minWindow(s, t) == "c");

		return true;
	}
};