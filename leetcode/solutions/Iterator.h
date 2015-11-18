#pragma once

#include <vector>

using namespace std;

class Iterator {
    const vector<int>& m_nums;
    size_t m_currentIndex;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};

Iterator::Iterator(const vector<int>& nums)
    : m_nums(nums)
    , m_currentIndex(0)
{}

Iterator::Iterator(const Iterator& iter)
    : m_nums(iter.m_nums)
    , m_currentIndex(0)
{}

Iterator::~Iterator()
{}

int Iterator::next()
{
    return m_nums[m_currentIndex++];
}

bool Iterator::hasNext() const
{
    return m_currentIndex < m_nums.size();
}
