#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/maximum-subarray/
class MaximumSubarray
{
public:
	// suppose we have found the max sub array: [i, j], and the max is larger than 0
	// then for any k, i<=k<j, we must have the sum of [i,k] >= 0
	// otherwise, [k+1, j] is larger than [i, j], which is conflict with assumption
	// So, when we travel the array, we assign the sum to 0 whenever we get the sum less than 0
	int maxSubArray(vector<int>& nums) 
	{
		assert(nums.size() > 0);

		int maxSum = INT_MIN;

		int end = 0;
		int sum = 0;
		for (end = 0; end < nums.size(); ++end)
		{
			sum += nums[end];

			maxSum = max(maxSum, sum);
			// sum could be less than 0 always,
			// or because of nums[end], which is less than 0, and make sum less than 0
			// find the next possible max sub array
			if (sum < 0)
			{
				sum = 0;
			}
		}
		return maxSum;
	}

	bool Test()
	{
		vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
		assert(maxSubArray(nums) == 6);

		nums = { -2 };
		assert(maxSubArray(nums) == -2);

		nums = { -2, -6, -3, -9, -5, -1, -4 };
		assert(maxSubArray(nums) == -1);
		return true;
	}
};