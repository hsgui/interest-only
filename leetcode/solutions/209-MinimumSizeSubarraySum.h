#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/minimum-size-subarray-sum/
class MinimumSizeSubarraySum
{
public:
	// O(n)
	int minSubArrayLen(int s, vector<int>& nums) 
	{
		int minBegin = 0;
		int minLen = INT_MAX;

		int minSum = INT_MAX;

		int sum = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			sum += nums[i];
			if (sum >= s)
			{
				while (sum - nums[minBegin] >= s)
				{
					sum = sum - nums[minBegin];
					minBegin++;
				}
				if (minLen > i - minBegin + 1)
				{
					minLen = i - minBegin + 1;
					minSum = sum;
				}
			}
		}
		if (sum >= s)
		{
			return minLen;
		}
		return 0;
	}

	bool Test()
	{
		vector<int> nums = { 2, 3, 1, 2, 4, 3 };
		int s = 7;
		int expected = 2;

		assert(minSubArrayLen(s, nums) == expected);

		assert(minSubArrayLen(2, nums) == 1);

		assert(minSubArrayLen(100, nums) == 0);

		return true;
	}
};