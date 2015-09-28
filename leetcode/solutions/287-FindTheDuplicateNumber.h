#pragma once

#include <vector>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/find-the-duplicate-number/
// http://keithschwarz.com/interesting/code/?dir=find-duplicate
// tortoise and hare algorithm
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

		nums = { 2, 2,2,2,2 };
		assert(findDuplicate(nums) == 2);

		return true;
	}
};