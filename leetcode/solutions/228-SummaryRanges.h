#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

class SummaryRanges
{
public:
	vector<string> summaryRanges(vector<int>& nums) 
	{
		vector<string> ranges;

		return ranges;
	}

	bool Test()
	{
		vector<int> nums = { 0, 1, 2, 4, 5, 7 };
		vector<string> ranges;
		ranges = summaryRanges(nums);
	}
};