#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

class TwoSum{
public:
	vector<int> twoSum(vector<int>& nums, int target)
	{
		unordered_map<int, shared_ptr<vector<int>>> value2Index(nums.size());
		for (int i = 0; i < nums.size(); ++i)
		{
			if (value2Index.find(nums[i]) != value2Index.end())
			{
				if (value2Index[nums[i]]->size() <= 1)
				{
					value2Index[nums[i]]->push_back(i);
				}
			}
			else
			{
				shared_ptr<vector<int>> v = make_shared<vector<int>>();
				v->push_back(i);
				value2Index[nums[i]] = v;
			}
		}

		int firstIndex = 0, secondIndex = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			int firstValue = nums[i];
			if (value2Index.find(target - firstValue) != value2Index.end())
			{
				firstIndex = i;
				shared_ptr<vector<int>> seconds = value2Index[target - firstValue];
				if (target - firstValue != firstValue)
				{
					secondIndex = seconds->at(0);
					break;
				}
				if (seconds->size() > 1)
				{
					secondIndex = seconds->at(1);
					break;
				}
			}
		}
		
		indexes->clear();
		indexes->push_back(firstIndex + 1);
		indexes->push_back(secondIndex + 1);

		return *indexes;
	}

	bool Test()
	{
		vector<int> case1 = { 3, 2, 4 };
		int target1 = 6;

		vector<int> case2 = { 0, 4, 3, 0 };
		int target2 = 0;

		vector<int> expect1 = { 2, 3 };
		vector<int> expect2 = { 1, 4 };

		vector<int> actual1 = twoSum(case1, target1);
		assert(expect1[0] == actual1[0] && expect1[1] == actual1[1]);

		vector<int> actual2 = twoSum(case2, target2);
		assert(expect2[0] == actual2[0] && expect2[1] == actual2[1]);

		return true;
	}

private:
	shared_ptr<vector<int>> indexes = make_shared<vector<int>>(2);
};