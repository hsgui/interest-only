#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
class FindMinimumInRotatedSortedArrayII
{
public:
    int findMin(vector<int>& nums) {
        size_t low = 0;
        size_t high = nums.size() - 1;
        size_t middle;

        // min in [low, high]
        while (low < high)
        {
            // if there are two halfs currently, then nums[low] >= nums[high]
            // => there is only one half, so the min is nums[low]
            if (nums[low] < nums[high])
            {
                return nums[low];
            }
            // middle == low or low < middle < high
            // middle < high
            middle = (high - low) / 2 + low;
            if (nums[middle] > nums[high])
            {
                // there are two halfs currently, and middle is in the first half
                // min is in the second half
                // min must be in [middle+1, high]
                low = middle + 1;
            }
            else if (nums[middle] < nums[low])
            {
                // there are two halfs currently, and middle is in the second half
                // the first element is in the second half
                high = middle;
            }
            else
            {
                // nums[middle] >= nums[low] && nums[middle] <= nums[high]
                // if nums[middle] == nums[low] && nums[middle] == nums[high] 
                //        => min could at the left or right of middle
                // if nums[middle] == nums[low] && nums[middle] < nums[high]
                // if nums[middle] > nums[low] && nums[middle] == nums[high]
                //        => min is nums[low]
                // if nums[middle] > nums[low] && nums[middle] < nums[high] 
                //        => impossible
                if (nums[middle] == nums[low]
                    && nums[middle] == nums[high])
                {
                    low++;
                }
                else
                {
                    // high = middle
                    return nums[low];
                }
            }
        }

        return nums[low];
    }

    bool Test()
    {
        vector<int> nums = { 1 };
        assert(findMin(nums) == 1);
        nums = { 1, 2 };
        assert(findMin(nums) == 1);

        nums = { 2, 1 };
        assert(findMin(nums) == 1);

        nums = { 5, 6, 7, 1, 2 };
        assert(findMin(nums) == 1);

        nums = { 5, 6, 1, 2, 3 };
        assert(findMin(nums) == 1);

        nums = { 1, 2, 3 };
        assert(findMin(nums) == 1);

        nums = { 3, 1, 2 };
        assert(findMin(nums) == 1);

        nums = { 2, 2, 2, 3, 3, 3, 3 };
        assert(findMin(nums) == 2);

        nums = { 3, 3, 3, 3, 3, 2, 2, 2 };
        assert(findMin(nums) == 2);

        nums = { 3, 3, 3, 2, 2, 2, 3 };
        assert(findMin(nums) == 2);

        nums = { 2, 2, 3, 3, 3, 3, 2 };
        assert(findMin(nums) == 2);
        return true;
    }
};