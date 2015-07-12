#include <algorithm>
#include <memory>
#include <cassert>

#include "ListNode.h"

using namespace std;

// https://leetcode.com/problems/palindrome-linked-list/
class PalindromeLinkedList
{
public:
	// see 206
	ListNode* reverseLinkedList(ListNode* head)
	{
		if (head == nullptr)
		{
			return nullptr;
		}
		ListNode* currentReverseListHead = head;
		ListNode* nextNode = head->next;
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

	bool isPalindrome(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
		{
			return true;
		}
		ListNode* slowNode = head;
		ListNode* fastNode = head;
		while (fastNode->next != nullptr
			&& fastNode->next->next != nullptr)
		{
			slowNode = slowNode->next;
			fastNode = fastNode->next->next;
		}

		ListNode* secondHalfHead = slowNode->next;
		secondHalfHead = reverseLinkedList(secondHalfHead);

		ListNode* firstHalfHead = head;

		while (firstHalfHead != nullptr && secondHalfHead != nullptr)
		{
			if (firstHalfHead->val != secondHalfHead->val)
			{
				return false;
			}
			firstHalfHead = firstHalfHead->next;
			secondHalfHead = secondHalfHead->next;
		}

		return true;
	}

	bool Test()
	{
		ListNode l1(1);
		ListNode l2(2);
		ListNode l3(3);
		ListNode l4(4);
		ListNode l5(5);

		l1.next = &l2;
		l2.next = &l3;
		l3.next = &l4;
		l4.next = &l5;

		assert(isPalindrome(&l1) == false);

		l1.next = &l2;
		l2.next = &l3;
		l3.next = &l4;
		l4.next = &l5;
		l5.next = nullptr;
		l4.val = 2, l5.val = 1;
		assert(isPalindrome(&l1) == true);

		l1.next = &l2;
		l2.next = &l3;
		l3.next = &l4;
		l4.next = nullptr;
		l3.val = 2, l4.val = 1;
		assert(isPalindrome(&l1) == true);
		return true;
	}
};