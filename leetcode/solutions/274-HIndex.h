#pragma once

#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
//https://leetcode.com/problems/h-index/
class HIndex
{
public:
	// 0 <= h <= N;
	// if the correct value is h, then after we sort the citation desc, we must have:
	// citations[0]...citations[h-1] >= h, and citations[h] <= h;
	int hIndex(vector<int>& citations) 
	{
		if (citations.size() == 0)
		{
			return 0;
		}

		std::sort(citations.begin(), citations.end(), [](int a, int b) -> bool
		{
			return a > b;
		});

		int h = 0;
		for (; h < citations.size(); h++)
		{
			// citations[0..h-1] >= h, citations[h..n) <= h, hIndex must be h
			if (citations[h] <= h)
			{
				break;
			}
		}
		return h;
	}

	bool Test()
	{
		vector<int> citations = { 3, 0, 6, 1, 5 };
		assert(hIndex(citations) == 3);

		citations = { 0 };
		assert(hIndex(citations) == 0);

		citations = { 1 };
		assert(hIndex(citations) == 1);

		citations = { 2 };
		assert(hIndex(citations) == 1);

		citations = { 1,1 };
		assert(hIndex(citations) == 1);

		return true;
	}
};