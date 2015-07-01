#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>

class Utils
{
public:
	template<typename T> 
	static bool equalVectorVector(const std::vector<std::vector<T>>& a, const std::vector<std::vector<T>>& b)
	{
		if (a.size() != b.size())
		{
			return false;
		}
		for (int i = 0; i < a.size(); i++)
		{
			if (!equal(a[i].begin(), a[i].end(), b[i].begin()))
			{
				return false;
			}
		}
		return true;
	}

	static uint64_t align(uint64_t size, uint64_t alignment)
	{
		if (0 == size)
		{
			return alignment;
		}
		// 0 - alignment = 2^64 - alignment
		return (size + alignment - 1) & (0 - alignment);
	}

	static size_t mergeOrderedList(const std::vector<uint64_t>& firstList, 
								   const std::vector<uint64_t>& secondList, 
								   std::vector<uint64_t>& result)
	{
		size_t count = 0;
		std::vector<uint64_t>::const_iterator it1 = firstList.begin();
		std::vector<uint64_t>::const_iterator it2 = secondList.begin();

		while (it1 != firstList.end() && it2 != secondList.end())
		{
			if ((*it1) == (*it2))
			{
				result.push_back(*it1);
				count++;
				it1++;
				it2++;
			}
			else if ((*it1) > (*it2))
			{
				result.push_back(*it2);
				count++;
				it2++;
			}
			else
			{
				result.push_back(*it1);
				count++;
				it1++;
			}
		}
		if (it1 == firstList.end())
		{
			count += secondList.end() - it2;
			result.insert(result.end(), it2, secondList.end());
		}
		else
		{
			count += firstList.end() - it1;
			result.insert(result.end(), it1, firstList.end());
		}
		return count;
	}
};

#endif
