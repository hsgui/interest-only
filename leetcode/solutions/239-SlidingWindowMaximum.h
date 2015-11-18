#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/sliding-window-maximum/
// http://articles.leetcode.com/2011/01/sliding-window-maximum.html
// http://en.cppreference.com/w/cpp/container/deque
class SlidingWindowMaximum
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) 
    {
        vector<int> maxValuesInWindow;
        if (nums.size() == 0)
        {
            return maxValuesInWindow;
        }

        maxValuesInWindow.reserve(nums.size() - k + 1);
        
        deque<int> maxValueIndexDeque;
        // initialize deque
        for (int i = 0; i < k; ++i)
        {
            while (!maxValueIndexDeque.empty() && nums[i] >= nums[maxValueIndexDeque.back()])
            {
                maxValueIndexDeque.pop_back();
            }
            maxValueIndexDeque.push_back(i);
        }

        maxValuesInWindow.push_back(nums[maxValueIndexDeque.front()]);
        for (int i = k; i < nums.size(); ++i)
        {
            while (!maxValueIndexDeque.empty() && nums[i] >= nums[maxValueIndexDeque.back()])
            {
                maxValueIndexDeque.pop_back();
            }
            while (!maxValueIndexDeque.empty() && maxValueIndexDeque.front() <= i - k)
            {
                maxValueIndexDeque.pop_front();
            }
            maxValueIndexDeque.push_back(i);
            maxValuesInWindow.push_back(nums[maxValueIndexDeque.front()]);
        }

        return maxValuesInWindow;
    }

    bool Test()
    {
        vector<int> nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
        vector<int> maxValues = { 3, 3, 5, 5, 6, 7 };

        vector<int> actual = maxSlidingWindow(nums, 3);

        assert(std::equal(actual.begin(), actual.end(), maxValues.begin()));
        return true;
    }
};