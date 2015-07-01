#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>
#include "Utils.h"

class UnitTest_Utils
{
public:
	bool Test();

	bool Test_MergeOrderedList();
};

bool
UnitTest_Utils::Test_MergeOrderedList()
{
	std::vector<uint64_t> list1 = {1, 2, 3, 6, 10};
	std::vector<uint64_t> list2 = { 1, 3, 5, 7, 8, 10, 12 };
	std::vector<uint64_t> expected = { 1, 2, 3, 5, 6, 7, 8, 10, 12 };
	std::vector<uint64_t> result;
	size_t count = Utils::mergeOrderedList(list1, list2, result);
	assert(equal(result.begin(), result.end(), expected.begin()));
	assert(count == result.size());
	return true;
}

bool
UnitTest_Utils::Test()
{
	Test_MergeOrderedList();

	return true;
}