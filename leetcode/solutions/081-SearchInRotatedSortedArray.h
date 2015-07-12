#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

class SearchInRotatedSortedArray
{
public:
	int search(vector<int>& nums, int target) {
		size_t low = 0;
		size_t high = nums.size() - 1;
		size_t middle;

		while (low < high)
		{
			// middle == low or low < middle < high
			// middle < high
			middle = (high - low) / 2 + low;

			if (nums[middle] == target)
			{
				return middle;
			}
			if (nums[low] < nums[high])
			{
				if (nums[middle] < target)
				{
					low = middle + 1;
				}
				else
				{
					high = middle - 1;
				}
			}
			else
			{
				// nums[low] > nums[high]
				// there are two halfs currently
				if (nums[middle] >= nums[low])
				{
					// middle is in the first half,
					if (nums[middle] < target)
					{
						// target must in the first half
						low = middle + 1;
					}
					else
					{
						if (target >= nums[low])
						{
							// target is the first half
							high = middle - 1;
						}
						else
						{
							low = middle + 1;
						}
					}
				}
				else
				{
					// middle is in the second half
					if (nums[middle] < target)
					{
						if (target >= nums[low])
						{
							// target is in the first half
							high = middle - 1;
						}
						else
						{
							low = middle + 1;
						}
					}
					else
					{
						// target is in the second half
						high = middle - 1;
					}
				}
			}
		}

		if (nums[low] == target)
		{
			return low;
		}
		return -1;
	}

	bool Test()
	{
		vector<int> nums = { 4, 5, 6, 7, 8, 1, 2, 3, };
		assert(search(nums, 4) == 0);
		assert(search(nums, 5) == 1);
		assert(search(nums, 6) == 2);
		assert(search(nums, 7) == 3);
		assert(search(nums, 8) == 4);
		assert(search(nums, 1) == 5);
		assert(search(nums, 2) == 6);
		assert(search(nums, 3) == 7);
		assert(search(nums, 9) == -1);

		nums = { 3, 1 };
		assert(search(nums, 1) == 1);
		assert(search(nums, 3) == 0);
		assert(search(nums, 4) == -1);

		nums = { 1, 2 };
		assert(search(nums, 1) == 0);
		assert(search(nums, 2) == 1);
		return true;
	}
};