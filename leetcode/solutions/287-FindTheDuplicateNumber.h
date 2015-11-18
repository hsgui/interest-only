#pragma once

#include <vector>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/find-the-duplicate-number/
// http://keithschwarz.com/interesting/code/?dir=find-duplicate -- excellent explanation
// tortoise and hare algorithm
class FindTheDuplicateNumber
{
public:
    int findDuplicate(vector<int>& nums) 
    {
        size_t n = nums.size() - 1;
        
        size_t slow = 0;
        size_t fast = 0;
        size_t finder = 0;

        while (true)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast)
            {
                break;
            }
        }
        // slow is the the smallest number that larger than c and multiple of l
        while (true)
        {
            slow = nums[slow];
            finder = nums[finder];
            if (slow == finder)
            {
                break;
            }
        }

        return slow;
    }

    bool Test()
    {
        vector<int> nums = { 2, 4, 5, 1, 2, 3 };
        assert(nums.size() == 6);

        assert(findDuplicate(nums) == 2);

        nums = { 2, 2,2,2,2 };
        assert(findDuplicate(nums) == 2);

        return true;
    }
};