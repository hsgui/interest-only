#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

// http://www.bubuko.com/infodetail-1151393.html
// https://leetcode.com/problems/find-median-from-data-stream/
// http://stackoverflow.com/questions/10657503/find-running-median-from-a-stream-of-integers
class MedianFinder {
public:
	// Adds a number into the data structure.
	void addNum(int num) {
		// maxHeap.size() >= minHeap.size();
		// maxHeap.top <= "median" <= minHeap.top
		maxHeap.push(num);
		int topInMaxHeap = maxHeap.top();
		maxHeap.pop();
		minHeap.push(topInMaxHeap);
		if (minHeap.size() > maxHeap.size())
		{
			maxHeap.push(minHeap.top());
			minHeap.pop();
		}
	}

	// Returns the median of current data stream
	double findMedian() {
		size_t maxHeapSize = maxHeap.size();
		size_t minHeapSize = minHeap.size();

		assert(maxHeapSize >= minHeapSize);

		if (maxHeapSize == 0 && minHeapSize == 0)
		{
			return 0;
		}
		else if (maxHeapSize == minHeapSize)
		{
			return (maxHeap.top() + (double)minHeap.top()) / 2;
		}
		else
		{
			assert(maxHeapSize == minHeapSize + 1);
			return maxHeap.top();
		}
	}

	bool Test()
	{
		MedianFinder finder;
		finder.addNum(2);
		finder.addNum(3);
		assert(finder.findMedian() == 2.5);
		return true;
	}

private:
	priority_queue<int, vector<int>, less<int>> maxHeap; // the smaller half that less than median
	priority_queue<int, vector<int>, greater<int>> minHeap; // the bigger half that greater than median
};