#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

class LRUCache{
public:
	LRUCache(int capacity)
	{
		m_capacity = capacity;
	}

	int get(int key)
	{
		return 0;
	}

	void set(int key, int value)
	{

	}

	bool Test()
	{
		LRUCache cache(2);
		cache.set(1, 1);
		cache.set(2, 2);
		assert(cache.get(1) == 1);
		assert(cache.get(2) == 2);

		cache.set(3, 3);
		assert(cache.get(1) == -1);
		assert(cache.get(3) == 3);

		return true;
	}

private:
	int m_capacity;
};