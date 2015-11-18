#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <sstream>

using namespace std;

class SummaryRanges
{
public:
    vector<string> summaryRanges(vector<int>& nums) 
    {
        vector<string> ranges;
        if (nums.size() == 0)
        {
            return ranges;
        }
        int first = nums[0];
        int last = first;
        for (int index = 1; index < nums.size(); index++)
        {
            int current = nums[index];
            if (current == last + 1)
            {
                last = current;
            }
            else
            {
                stringstream ss;
                if (first < last)
                {
                    ss << first << "->" << last;
                }
                else
                {
                    ss << first;
                }
                ranges.push_back(ss.str());
                first = current;
                last = current;
            }
        }
        stringstream ss;
        if (first < last)
        {
            ss << first << "->" << last;
        }
        else
        {
            ss << first;
        }
        ranges.push_back(ss.str());

        return ranges;
    }

    bool Test()
    {
        vector<int> nums = { 0, 1, 2, 4, 5, 7 };
        vector<string> expected = {
            "0->2",
            "4->5",
            "7"
        };
        vector<string> ranges;
        ranges = summaryRanges(nums);
        assert(equal(expected.begin(), expected.end(), ranges.begin()));

        nums = {};
        ranges = summaryRanges(nums);
        assert(ranges.size() == 0);

        nums = { 1 };
        expected = { "1" };
        ranges = summaryRanges(nums);
        assert(equal(expected.begin(), expected.end(), ranges.begin()));

        return true;
    }
};