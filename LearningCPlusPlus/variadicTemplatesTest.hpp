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

		template<typename T>
		struct iremove_reference
		{
			typedef T type;
		};

		template<typename T>
		struct iremove_reference<T&>
		{
			typedef T type;
		};

		template<typename T>
		struct iremove_reference<T&&>
		{
			typedef T type;
		};

		template<typename T>
		size_t countOccurrences(std::vector<T>& p_values, const T& v)
		{
			std::cout << "original template is called" << std::endl;
			size_t occurrence = 0;
			for (const T& element : p_values)
			{
				if (element == v) occurrence++;
			}

			return occurrence;
		}

		template<>
		size_t countOccurrences(std::vector<const char*>& p_values, const char* const& v)
		{
			std::cout << "specialization of const char* is called" << std::endl;
			size_t occurrences = 0;
			for (const char* element : p_values)
			{
				if (std::strcmp(element, v) == 0) occurrences++;
			}
			return occurrences;
		}

		void test()
		{
			foo(23, 1.1, "hello", 0xde);
			iprint(std::cout, 23, 1.1, "hello", 0xde);

			iremove_reference<decltype(42)>::type i = 0;
			std::cout << "iremove_reference<decltype(42)>::type i = " << i << std::endl;

			iremove_reference<decltype(std::move(i))>::type j = 0;
			std::cout << "iremove_reference<decltype(std::move(i))>::type j = " << j << std::endl;

			std::vector<std::string> values1 = { "hello", "world", "hello" };
			std::cout << "occurrences = " << countOccurrences(values1, std::string("hello")) << std::endl;

			std::vector<const char*> values2 = { "hello", "world", "hello" };
			const char* value = "hello";
			std::cout << "occurrences = " << countOccurrences(values2, value) << std::endl;
		}
	}	
}