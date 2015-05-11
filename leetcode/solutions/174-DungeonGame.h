#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/dungeon-game/
class DunGeonGame
{
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon)
	{
		int minimumHP = 0;

		return minimumHP;
	}

	bool Test()
	{
		vector<vector<int>> dungeon = 
		{
			{-2, -3, 3},
			{-5, -10, 1},
			{10, 30, -5}
		};
		int minimumHP = 7;
		int actual = calculateMinimumHP(dungeon);
		assert(actual == minimumHP);
	}
};