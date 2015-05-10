#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

class SearchForARange{
public:
	vector<int> searchRange(vector<int>& nums, int target)
	{
		vector<int> range;
		int left = -1, right = nums.size();
		while (left + 1 < right)
		{
			int middle = (right - left) / 2 + left;
			if (nums[middle] >= target)
			{
				right = middle;
			}
			else
			{
				left = middle;
			}
		}
		if (left + 1 >= nums.size() ||  nums[left + 1] != target)
		{
			range.push_back(-1);
		}
		else
		{
			range.push_back(left + 1);
		}
		left = -1, right = nums.size();
		while (left + 1 < right)
		{
			int middle = (right - left) / 2 + left;
			if (nums[middle] <= target)
			{
				left = middle;
			}
			else
			{
				right = middle;
			}
		}
		if (right - 1 < 0 || nums[right - 1] != target)
		{
			range.push_back(-1);
		}
		else
		{
			range.push_back(right - 1);
		}
		return range;
	}

	bool Test()
	{
		vector<int> nums = { 5, 7, 7, 8, 8, 10 };
		vector<int> expected = { 3, 4 };
		vector<int> actual = searchRange(nums, 8);
		assert(equal(actual.begin(), actual.end(), expected.begin()));

		nums = { 8, 8, 8, 8, 8, 8 };
		expected = { 0, 5 };
		actual = searchRange(nums, 8);
		assert(equal(actual.begin(), actual.end(), expected.begin()));

		nums = { 1 };
		expected = { -1, -1 };
		actual = searchRange(nums, 0);
		assert(equal(actual.begin(), actual.end(), expected.begin()));

		actual = searchRange(nums, 2);
		assert(equal(actual.begin(), actual.end(), expected.begin()));

		return true;
	}
};