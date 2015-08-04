#pragma once

#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

class ValidAnagram
{
public:
	bool isAnagram(string s, string t) {
		const int size = 255;
		int count[size] = { 0 };
		for (int i = 0; i < s.size(); i++)
		{
			count[s[i]]++;
		}

		for (int i = 0; i < t.size(); ++i)
		{
			if (count[t[i]] == 0)
			{
				return false;
			}
			count[t[i]]--;
		}
		for (int i = 0; i < size; i++)
		{
			if (count[i] != 0)
			{
				return false;
			}
		}

		return true;
	}

	bool Test()
	{
		string s = "anagram";
		string t = "nagaram";
		assert(isAnagram(s, t) == true);

		s = "rat";
		t = "cat";
		assert(isAnagram(s, t) == false);
		return true;
	}
};