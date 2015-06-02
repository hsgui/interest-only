#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

#include "ListNode.h"

// https://leetcode.com/problems/intersection-of-two-linked-lists/
class IntersectionOfTwoLinkedList
{
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
	{
		if (headA == NULL || headB == NULL)
		{
			return NULL;
		}
		ListNode* tailA = headA;
		ListNode* tailB = headB;
		int lengthA = 1;
		int lengthB = 1;
		while (tailA->next != NULL)
		{
			lengthA++;
			tailA = tailA->next;
		}
		while (tailB->next != NULL)
		{
			lengthB++;
			tailB = tailB->next;
		}
		if (lengthA > lengthB)
		{
			for (int i = 1; i <= lengthA - lengthB; ++i)
			{
				headA = headA->next;
			}
		}
		else
		{
			for (int i = 1; i <= lengthB - lengthA; ++i)
			{
				headB = headB->next;
			}
		}
		int remainLength = min(lengthA, lengthB);
		int i;
		for (i = 1; i <= remainLength && headA != headB; ++i)
		{
			headA = headA->next;
			headB = headB->next;
		}
		if (i > remainLength)
		{
			return NULL;
		}
		else
		{
			assert(headA == headB);
			return headA;
		}
	}

	bool Test()
	{
		assert(getIntersectionNode(NULL, NULL) == NULL);
		ListNode l1(1);
		ListNode l2(2);
		ListNode l3(3);
		ListNode l4(4);
		ListNode l5(5);

		assert(getIntersectionNode(&l1, &l1) == &l1);
		l1.next = &l4;
		l2.next = &l3;
		l3.next = &l4;
		assert(getIntersectionNode(&l1, &l2) == &l4);

		l3.next = &l5;
		assert(getIntersectionNode(&l1, &l2) == NULL);
		return true;
	}
};