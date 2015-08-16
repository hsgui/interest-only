#pragma once

#include <vector>

using namespace std;

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
class BestTimeToBuyAndSellStock1
{
public:
	/*
		prices vector: a1, a2, a3, ... , an
		then, maxProfit = max(a_j - a_i) , j>=i
		that is: ... ai ... aj ... 
		then if we have found a_i, a_j, we must have:
		a_j = max(a_i, a_(i+1), ... , a_n)
		a_i = min(a_1, a_2, ..., a_i)
		or, if we have a_i, then, a_j = a_i + maxProfit
	*/
	int maxProfit(vector<int>& prices) {
		if (prices.size() == 0)
		{
			return 0;
		}
		int high = 0;
		int profit = 0;
		int minimal = prices[0];

		for (high = 1; high < prices.size(); ++high)
		{
			minimal = min(minimal, prices[high]);
			profit = max(profit, prices[high] - minimal);
		}
		return profit;
	}

	bool Test()
	{
		vector<int> prices = { 4,3,2,1 };
		int expected = 0;
		assert(maxProfit(prices) == expected);

		prices = { 3, 2, 1, 4, 8 };
		expected = 7;
		assert(maxProfit(prices) == expected);

		return true;
	}
};
