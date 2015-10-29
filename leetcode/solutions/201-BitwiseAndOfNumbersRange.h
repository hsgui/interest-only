#pragma once

#include <cassert>
// https://leetcode.com/problems/bitwise-and-of-numbers-range/
class BitwiseAndOfNumbersRange
{
public:
	int rangeBitwiseAnd(int m, int n) 
	{
		// if m < n, then the lowest bit must be 0
		size_t offset = 0;
		while (m < n)
		{
			m >>= 1;
			n >>= 1;
			offset++;
		}

		assert(m == n);
		return m << offset;
	}

	bool Test()
	{
		assert(rangeBitwiseAnd(5, 7) == 4);

		return true;
	}
};