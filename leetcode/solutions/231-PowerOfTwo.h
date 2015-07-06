#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/power-of-two/
class PowerOfTwo
{
public:
	bool isPowerOfTwo(int n) 
	{
		return (n > 0) && !(n & (n - 1));
	}

	bool Test()
	{
		assert(isPowerOfTwo(0) == false);
		assert(isPowerOfTwo(1) == true);
		assert(isPowerOfTwo(2) == true);
		assert(isPowerOfTwo(3) == false);
		assert(isPowerOfTwo(4) == true);
		assert(isPowerOfTwo(9) == false);
		assert(isPowerOfTwo(10) == false);
		assert(isPowerOfTwo(2147483647) == false);

		return true;
	}
};