#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

#include "ListNode.h"

// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

class RemoveNthNodeFromEndOfList
{
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) 
	{
		ListNode dump(0);
		dump.next = head;
		ListNode* p1 = &dump;
		ListNode* p2 = &dump;

		for (int i = 0; i < n; ++i)
		{
			assert(p2 != NULL);
			p2 = p2->next;
		}
		while (p2->next != NULL)
		{
			p2 = p2->next;
			p1 = p1->next;
		}
		if (n > 0)
		{
			p1->next = p1->next->next;
		}		

		return dump.next;
	}

	bool Test()
	{
		ListNode l1(1);
		ListNode l2(2);
		ListNode l3(3);
		ListNode l4(4);

		l1.next = &l2;
		l2.next = &l3;
		l3.next = &l4;

		ListNode* head = removeNthFromEnd(&l1, 0);
		for (int i = 1; i <= 4; i++)
		{
			assert(head->val == i);
			head = head->next;
		}
		assert(head == NULL);

		head = removeNthFromEnd(&l1, 1);
		assert(head->val == 1);
		head = head->next;
		assert(head->val == 2);
		head = head->next;
		assert(head->val == 3);
		assert(head->next == NULL);

		head = removeNthFromEnd(&l1, 2);
		assert(head->val == 1);
		head = head->next;
		assert(head->val == 3);
		assert(head->next == NULL);

		head = removeNthFromEnd(&l1, 2);
		assert(head->val == 3);
		assert(head->next == NULL);

		head = removeNthFromEnd(&l3, 1);
		assert(head == NULL);
		
		return true;
	}
};