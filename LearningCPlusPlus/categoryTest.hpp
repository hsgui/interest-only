#pragma once

#include <iostream>
#include "category.hpp"

namespace CategoryPractice
{
	int IntAbs(int num)
	{
		if (num < 0)
		{
			num = -num;
		}
		return num;
	}

	void testFmap()
	{
		std::shared_ptr<int> a(new int(-4));
		std::function<int(int)> f = IntAbs;
		std::shared_ptr<int> sabs = fmap(f, a);

		std::cout << "fmap(IntAbs, -4): " << *sabs << std::endl;
	}
}