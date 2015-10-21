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

	bool Test_RemoveDuplicatedElementFromSortedVector();

	bool Test_DedupItemsFromMultipleVectors();
};

bool
UnitTest_Utils::Test_MergeOrderedList()
{
	std::cout << "Test Merge Ordered list" << std::endl;
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
UnitTest_Utils::Test_RemoveDuplicatedElementFromSortedVector()
{
	std::cout << "Test RemoveDuplicatedElementFromSortedVector" << std::endl;
	std::vector<int> list = { 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 8, 8 };
	std::vector<int> list2 = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7, 8 };
	Utils::removeDuplicatedElementFromSortedVector(list);
	assert(list.size() == expected.size());
	assert(equal(list.begin(), list.end(), expected.begin()));

	Utils::removeDuplicatedElementFromSortedVector(list2);
	assert(list2.size() == expected.size());
	assert(equal(list2.begin(), list2.end(), expected.begin()));

	return true;
}

bool
UnitTest_Utils::Test_DedupItemsFromMultipleVectors()
{
	std::cout << "Test DedupItemsFromMultipleVectors" << std::endl;
	Utils::MultipleLevelVector v1;
	v1.m_version = 2;
	v1.m_items = { 1, 1, 3, 5, 5, 4, 4, 4, 8, 7 };

	Utils::MultipleLevelVector v2;
	v2.m_version = 1;
	v2.m_items = { 1, 1, 0, 0, 5, 3, 4, 7, 8, 9, 9 };

	Utils::MultipleLevelVector v3;
	v3.m_version = 3;
	v3.m_items = { 9 };

	std::vector<Utils::MultipleLevelVector> levelVectors;
	Utils::dedupItemFromMultipleVectors(levelVectors);

	levelVectors.push_back(v1);
	levelVectors.push_back(v2);
	levelVectors.push_back(v3);

	Utils::dedupItemFromMultipleVectors(levelVectors);

	return true;
}

bool
UnitTest_Utils::Test()
{
	Test_MergeOrderedList();

	Test_RemoveDuplicatedElementFromSortedVector();

	Test_DedupItemsFromMultipleVectors();

	return true;
}