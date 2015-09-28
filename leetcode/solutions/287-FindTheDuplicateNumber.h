#pragma once

#include <vector>
#include <cassert>

using namespace std;

class FindTheDuplicateNumber
{
public:
	int findDuplicate(vector<int>& nums) 
	{
		size_t n = nums.size() - 1;
		int sumOfN = ((n + 1) * n) / 2;
		int sumOfNums = 0;
		for (int ele : nums)
		{
			sumOfNums += ele;
		}

		return sumOfNums - sumOfN;
	}

	bool Test()
	{
		vector<int> nums = { 2, 4, 5, 1, 2, 3 };
		assert(nums.size() == 6);

		assert(findDuplicate(nums) == 2);

		return true;
	}
};