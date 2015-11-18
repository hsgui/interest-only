#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
class FindMinimumInRotatedSortedArray
{
public:
    int findMin(vector<int>& nums) {
        size_t low = 0;
        size_t high = nums.size() - 1;
        size_t middle;

        // min in [low, high]
        while (low < high)
        {
            // middle == low or low < middle < high
            // middle < high
            middle = (high - low) / 2 + low;
            if (nums[low] < nums[middle] && nums[middle] > nums[high])
            {
                // there are two halfs currently, and middle is in the first half
                low = middle + 1;
                // min must be in [middle+1, high]
            }
            else if (nums[low] < nums[middle] && nums[middle] <= nums[high])
            {
                // there are only one half currently, 
                // the first element is the min
                return nums[low];
            }
            else if (nums[low] >= nums[middle] && nums[middle] < nums[high])
            {
                // if nums[low] > nums[middle]
                //        there are two halfs currently, and the middle is in the second halfs
                // if nums[low] == nums[middle]
                //        there is one half currently, and the min is nums[low]
                // min must in [low, high - 1]
                if (nums[low] > nums[middle])
                {
                    // handle the special case: [5, 1, 2, 3, 4]
                    low = low + 1;
                }
                high = high - 1;
            }
            else if (nums[low] >= nums[middle] && nums[middle] >= nums[high])
            {
                // min must nums[high]
                return nums[high];
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
        return true;
    }
};