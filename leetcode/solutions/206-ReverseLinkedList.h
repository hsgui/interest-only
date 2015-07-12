#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

#include "ListNode.h"

class ReverseLinkedList
{
public:
	ListNode* reverseList(ListNode* head)
	{
		return reverseListRecursively(head);
	}

	ListNode* reverseListIteratively(ListNode* head)
	{
		if (head == nullptr)
		{
			return nullptr;
		}
		ListNode* currentReverseListHead = head;
		ListNode* nextNode = currentReverseListHead->next;
		currentReverseListHead->next = nullptr;
		while (nextNode != nullptr)
		{
			ListNode* nextNext = nextNode->next;
			nextNode->next = currentReverseListHead;
			currentReverseListHead = nextNode;
			nextNode = nextNext;
		}

		return currentReverseListHead;
	}

	ListNode* reverseListRecursively(ListNode* head)
	{
		ListNode* tail;
		return reverseListRecursivelyHelper(head, tail);
	}

	ListNode* reverseListRecursivelyHelper(ListNode* head, ListNode* & tail)
	{
		if (head == NULL)
		{
			tail = NULL;
			return NULL;
		}
		if (head->next == NULL)
		{
			tail = head;
			return head;
		}
		ListNode* reversedHead = reverseListRecursivelyHelper(head->next, tail);
		tail->next = head;
		tail = head;
		tail->next = NULL;
		return reversedHead;
	}

	bool Test()
	{
		assert(reverseList(NULL) == NULL);

		ListNode l1(1);
		ListNode* r = reverseList(&l1);
		assert(r->val == 1 && r->next == NULL);

		ListNode* current = &l1;
		for (int i = 2; i < 10; ++i)
		{
			ListNode* n = new ListNode(i);
			current->next = n;
			current = n;
		}
		r = reverseList(&l1);
		current = r;
		for (int i = 9; i >= 1; --i)
		{
			assert(current != NULL);
			assert(current->val == i);
			current = current->next;
		}
		assert(current == NULL);
		return true;
	}
};