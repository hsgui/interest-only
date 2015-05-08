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
	void sortColorsV2(vector<int>& nums)
	{
		int left = -1, right = nums.size() ;
		int curr = 0;
		while (curr < right && left < curr)
		{
			switch (nums[curr])
			{
			case 0:
				swap(nums[curr], nums[++left]);
				curr++;
				break;
			case 1:
				curr++;
				break;
			case 2:
				swap(nums[curr], nums[--right]);
				break;
			}
		}
	}

	bool Test()
	{
		vector<int> v = { 1, 1, 2, 0, 1, 2, 0, 0, 1 };
		vector<int> e = { 0, 0, 0, 1, 1, 1, 1, 2, 2 };
		sortColorsV2(v);
		assert(equal(v.begin(), v.end(), e.begin()));

		v = { 0, 2, 1 };
		e = { 0, 1, 2 };
		sortColorsV2(v);
		assert(equal(v.begin(), v.end(), e.begin()));

		return true;
	}
};