#pragma once

#include <iostream>
#include "bubbleSort.hpp"
#include <cassert>

namespace TemplatePractice {

	void testBubbleSort()
	{
		const int size = 8;
		int num[size] = { 8,7,6,5,4,3,2,1 };
		IntBubbleSort<size>::sort(num);

		for (int i = 1; i <= size; ++i)
		{
			assert(i == num[i - 1]);
		}
		std::cout << "test bubble sort successfully!" << std::endl;
	}
}