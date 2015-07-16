#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/product-of-array-except-self/
class ProductOfArrayExceptSelf
{
public:
	vector<int> productExceptSelf(vector<int>& nums) 
	{
		assert(nums.size() > 0);

		vector<int> products;
		products.resize(nums.size());

		int productInOnePass = 1;
		for (int i = 0; i < nums.size(); ++i)
		{
			products[i] = productInOnePass;
			productInOnePass *= nums[i];
		}
		productInOnePass = 1;
		for (int i = nums.size() - 1; i >= 0; --i)
		{
			products[i] *= productInOnePass;
			productInOnePass *= nums[i];
		}

		return products;
	}

	bool Test()
	{
		vector<int> nums = { 1, 2, 3, 4 };
		vector<int> expected = { 24, 12, 8, 6 };
		vector<int> actual = productExceptSelf(nums);
		assert(equal(expected.begin(), expected.end(), actual.begin()));

		nums = { 1, 2 };
		expected = { 2, 1 };
		actual = productExceptSelf(nums);
		assert(equal(expected.begin(), expected.end(), actual.begin()));

		return true;
	}
};