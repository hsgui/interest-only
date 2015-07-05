#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/kth-largest-element-in-an-array/
class KthLargestElementInArray
{
public:
	// partition [p, q] in quicksort
	int partition(vector<int>& nums, int p, int q)
	{
		int pivot = nums[p];
		int i = p;
		for (int j = p + 1; j <= q; ++j)
		{
			if (nums[j] < pivot)
			{
				swap(nums[++i], nums[j]);
			}
		}
		swap(nums[p], nums[i]);
		return i;
	}

	int select(vector<int>& nums, int start, int end, int k)
	{
		int p = partition(nums, start, end);
		// [start, p - 1] < [p] <= [p, end]
		int kindex = end - k + 1;
		if (kindex == p)
		{
			return nums[kindex];
		}
		else if (p < kindex)
		{
			return select(nums, p + 1, end, k);
		}
		else
		{
			return select(nums, start, p - 1, k - (end - p + 1));
		}
	}

	int findKthLargest(vector<int>& nums, int k) 
	{
		int start = 0;
		int end = nums.size() - 1;

		return select(nums, start, end, k);
	}

	bool Test()
	{
		vector<int> nums = { 3, 2, 1, 5, 6, 4, 5 };
		assert(findKthLargest(nums, 1) == 6);
		assert(findKthLargest(nums, 2) == 5);
		assert(findKthLargest(nums, 3) == 5);
		assert(findKthLargest(nums, 4) == 4);
		assert(findKthLargest(nums, 5) == 3);
		assert(findKthLargest(nums, 6) == 2);
		assert(findKthLargest(nums, 7) == 1);

		return true;
	}
};