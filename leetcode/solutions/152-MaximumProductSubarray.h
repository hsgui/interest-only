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
			assert(minproduct <= maxproduct);
			if (nums[i] > 0)
			{
				int maxIncludeCurrent = maxproduct * nums[i];
				int minIncludeCurrent = minproduct * nums[i];
				maxproduct = max(nums[i], maxIncludeCurrent);
				minproduct = minIncludeCurrent;
				result = max(result, maxproduct);
			}
			else if (nums[i] < 0)
			{
				int minIncludeCurrent = maxproduct * nums[i];
				int maxIncludeCurrent = minproduct * nums[i];
				maxproduct = max(maxIncludeCurrent, minIncludeCurrent);
				minproduct = min(maxIncludeCurrent, minIncludeCurrent);
				minproduct = min(minproduct, nums[i]);
				result = max(result, maxproduct);
			}
			else
			{
				minproduct = 1;
				maxproduct = 1;
				result = max(result, 0);
			}
		}
		return result;
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

		nums = { 2, -5, -2, -4, 3 };
		assert(maxProduct(nums) == 24);
		return true;
	}
};