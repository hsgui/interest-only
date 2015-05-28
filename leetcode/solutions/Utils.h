#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>

class Utils
{
public:
	template<typename T> 
	static bool equalVectorVector(const vector<vector<T>>& a, const vector<vector<T>>& b)
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
};

#endif
