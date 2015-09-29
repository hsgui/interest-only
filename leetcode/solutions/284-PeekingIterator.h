#pragma once

#include <vector>
#include <cassert>
#include "Iterator.h"

class PeekingIterator : public Iterator
{
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.
		m_hasPeeked = false;
	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		if (!m_hasPeeked)
		{
			m_nextElement = Iterator::next();
			m_hasPeeked = true;
		}

		return m_nextElement;
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		if (!m_hasPeeked)
		{
			return Iterator::next();
		}
		m_hasPeeked = false;

		return m_nextElement;
	}

	bool hasNext() const {
		return m_hasPeeked || Iterator::hasNext();
	}

	bool Test()
	{
		vector<int> nums = { 1,2,3,4,5,6 };
		PeekingIterator it(nums);

		assert(it.hasNext());
		assert(it.next() == 1);
		assert(it.peek() == 2);
		assert(it.next() == 2);
		assert(it.hasNext());

		assert(it.peek() == 3);
		assert(it.hasNext());
		assert(it.peek() == 3);
		assert(it.next() == 3);
		assert(it.peek() == 4);
		assert(it.next() == 4);
		assert(it.next() == 5);
		assert(it.peek() == 6);
		assert(it.hasNext());
		assert(it.next() == 6);
		assert(it.hasNext() == false);

		return true;
	}

private:
	bool m_hasPeeked;
	int m_nextElement;
};