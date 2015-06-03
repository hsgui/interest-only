#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/maximum-product-subarray/
// http://www.geeksforgeeks.org/maximum-product-subarray/
class MaximumProductSubarray
{
public:

	// time: O(n), space: O(1)
	// first consider the situation that the array doesn't contain 0
	// then consider the situation that the array does contain 0
	int maxProduct(vector<int>& nums)
	{
		assert(nums.size() > 0);
		int result = nums[0];
		int maxproduct = nums[0];
		int minproduct = nums[0];
		for (int i = 1; i < nums.size(); ++i)
		{
			if (nums[i] > 0)
			{
				
			}
		}
		return 0;
	}

	bool Test()
	{
		vector<int> nums = { 6, -3, -10, 0, 2 };
		assert(maxProduct(nums) == 180);

		nums = { -1, -3, -10, 0, 60 };
		assert(maxProduct(nums) == 60);

		nums = { -2, -3, 0, -2, -40 };
		assert(maxProduct(nums) == 80);

		nums = { 0, 0, -20, 0 };
		assert(maxProduct(nums) == 0);

		nums = { 0, 0, 0, 0 };
		assert(maxProduct(nums) == 0);
		return true;
	}
};