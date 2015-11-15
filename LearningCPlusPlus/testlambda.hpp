#pragma once

#include <iostream>
#include <vector>
#include <functional>

namespace LearningCPP
{
	namespace Lambda
	{
		using FilterContainer = std::vector<std::function<bool(int)>>;
		FilterContainer filters;

		int computeDivisor()
		{
			return rand();
		}

		void addDivisorFilter()
		{
			int divisor = computeDivisor();
			filters.emplace_back([&](int value) {return value % divisor == 0; });

			filters.emplace_back([&divisor](int value) {return value % divisor == 0; });
		}

		void test()
		{
			long long x = 4;
			// capture by copy
			auto c1 = [x](int y) {return x*y > 55; };
			// the type of c1 is a function class - closure type.
			// c1 itself is a closure.
			// sizeof(c1) == 8
			std::cout << "typename(c1)="<< typeid(c1).name() <<", sizeof(c1)=" << sizeof(c1) << std::endl;
			std::cout << "c1(18)=" << c1(18) << std::endl;

			// closure is copied
			auto c2 = c1;
			std::cout << "c2(18)=" << c2(18) << std::endl;

			addDivisorFilter();
			std::cout << "filters[0](12) = " << filters[0](12) << std::endl;
		}
	}
}