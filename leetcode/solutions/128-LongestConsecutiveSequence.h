#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

class LongestConsecutiveSequence{
public:
	int longestConsecutive(vector<int>& nums)
	{
		unordered_set<int> allNums(nums.size());
		for (int i = 0; i < nums.size(); ++i)
		{
			allNums.insert(nums[i]);
		}
		int longest = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			int current = nums[i];
			int currentLength = 1;
			unordered_set<int>::iterator it;
			if ((it = allNums.find(current)) != allNums.end())
			{
				currentLength = 1;
				current = nums[i] + 1;
				while ((it = allNums.find(current)) != allNums.end())
				{
					++currentLength;
					++current;
					allNums.erase(it);
				}
				current = nums[i] - 1;
				while ((it = allNums.find(current)) != allNums.end())
				{
					++currentLength;
					--current;
					allNums.erase(it);
				}
			}
			if (longest < currentLength)
			{
				longest = currentLength;
			}
		}
		return longest;
	}

	bool Test()
	{
		vector<int> n = { 100, 4, 200, 1, 3, 2 };
		int longest = 4;
		assert(longestConsecutive(n) == longest);
		
		return true;
	}
};