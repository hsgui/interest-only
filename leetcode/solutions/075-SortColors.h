#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

class SortColors
{
public:
	// two-pass algorithm
	void sortColors(vector<int>& nums)
	{
		const int colorNum = 3;
		int count[colorNum] = { 0 };
		vector<int>::iterator it;
		for (it = nums.begin(); it != nums.end(); ++it)
		{
			count[*it]++;
		}
		int index = 0;
		for (int i = 0; i < colorNum; i++)
		{
			for (int j = 0; j < count[i]; ++j)
			{
				nums[index++] = i;
			}
		}
	}

	// one-pass algorithm
	void sortColors(vector<int>& nums)
	{

	}

	bool Test()
	{
		vector<int> v = { 1, 1, 2, 0, 1, 2, 0, 0, 1 };
		vector<int> e = { 0, 0, 0, 1, 1, 1, 1, 2, 2 };
		sortColors(v);
		assert(equal(v.begin(), v.end(), e.begin()));

		return true;
	}
};