#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/maximum-subarray/
class MaximumSubarray
{
public:
	int maxSubArray(vector<int>& nums) 
	{
		assert(nums.size() > 0);

		int maxSum = nums[0];

		int begin = 0;
		int end = 0;
		int sum = nums[0];
		for (end = 1; end < nums.size(); ++end)
		{
		}
		return maxSum;
	}

	bool Test()
	{
		vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
		assert(maxSubArray(nums) == 6);

		nums = { -2 };
		assert(maxSubArray(nums) == -2);
		return true;
	}
};