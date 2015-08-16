#pragma once

#include <vector>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
class BestTimeToBuyAndSellStock2 {
public:
	/*
		continue with the BestTimeToBuyAndSellStock1
		suppose we only consider the following range (a_i, a_j makes the max profit in 1):
		a_i, ... , a_j,
		then, if [a_i, ..., a_j] are non-decrease, 
		then no matter how many transactions occurs between a_i and a_j,
		the max profit will be a_j - a_i
		if not, then, we must have two values, a_m, a_n,
		and a_i < a_m, a_m > a_n, a_n < a_j, ( i < m < n < j)
		the max profit = a_j - a_n + a_m - a_i > the max profit in 1
	*/
	int maxProfit(vector<int>& prices) {
		if (prices.size() == 0) {
			return 0;
		}

		int profit = 0;
		int minimal = prices[0];
		for (int current = 1; current < prices.size(); current++) {
			if (prices[current] > minimal) {
				// whenever we get a profit, sell it
				profit += prices[current] - minimal;
				minimal = prices[current];
			}
			else
			{
				minimal = prices[current];
			}
		}

		return profit;
	}

	bool Test()
	{
		vector<int> prices = { 3,2,1,4,8 };
		int profit = 7;
		assert(maxProfit(prices) == profit);

		prices = { 1, 4, 2, 3, 4, 9, 2, 1 };
		profit = 10;
		assert(maxProfit(prices) == profit);

		return true;
	}
};