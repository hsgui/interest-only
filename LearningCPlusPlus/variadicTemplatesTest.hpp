#pragma once

#include <iostream>
#include <ostream>

namespace LearningCPP
{
	namespace VariadicTemplate
	{
		template<typename T, typename... Args>
		void foo(const T& t, const Args& ... rest)
		{
			std::cout << "sizeof...(Args) = " << sizeof...(Args) << std::endl;
			std::cout << "sizeof...(rest) = " << sizeof...(rest) << std::endl;
		}

		template<typename T>
		std::ostream& iprint(std::ostream& os, const T& t)
		{
			return os << t << std::endl;
		}

		template<typename T, typename... Args>
		std::ostream& iprint(std::ostream& os, const T& t, const Args& ... rest)
		{
			os << t << ", ";
			return iprint(os, rest...);
		}

		void test()
		{
			foo(23, 1.1, "hello", 0xde);
			iprint(std::cout, 23, 1.1, "hello", 0xde);
		}
	}	
}