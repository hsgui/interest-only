#pragma once

#include <set>
#include <vector>

namespace LearningCPP
{
	namespace QuickStart
	{
		template<typename... Ts>
		void iprintf(const char* format, Ts&&... params)
		{
			printf(format, std::forward<Ts>(params)...);
			printf("\n");
		}

		void test()
		{
			std::vector<int> a{ 1,2,3,7,4,5 };
			std::vector<int> b{ 6,3,2,7,9,1 };
			std::set<int> combined;
			combined.insert(a.begin(), a.end());
			combined.insert(b.begin(), b.end());

			iprintf("%s, %d", "hello world", 5);

			return;
		}
	}
}