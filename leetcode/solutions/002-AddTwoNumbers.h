#pragma once

#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

#include "ListNode.h"

using namespace std;

// https://leetcode.com/problems/add-two-numbers/
class AddTwoNumbers
{
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* sum = nullptr;
		ListNode* previous = sum;
		int carry = 0;

		while (l1 != nullptr || l2 != nullptr)
		{
			int sumOfTwoDigits = carry;
			if (l1 != nullptr)
			{
				sumOfTwoDigits += l1->val;
				l1 = l1->next;
			}
			if (l2 != nullptr)
			{
				sumOfTwoDigits += l2->val;
				l2 = l2->next;
			}

			if (sumOfTwoDigits >= 10)
			{
				sumOfTwoDigits -= 10;
				carry = 1;
			}
			else
			{
				carry = 0;
			}

			ListNode* l = new ListNode(sumOfTwoDigits);
			if (sum == nullptr)
			{
				sum = l;
				previous = l;
			}
			else
			{
				previous->next = l;
				previous = l;
			}
		}

		if (carry != 0)
		{
			ListNode* l = new ListNode(carry);
			previous->next = l;
		}
		
		return sum;
	}

	bool Test()
	{
		assert(addTwoNumbers(nullptr, nullptr) == nullptr);

		ListNode l1(8);
		ListNode l2(9);
		ListNode l3(9);

		l1.next = &l2;
		l2.next = &l3;

		ListNode l4(9);
		ListNode l5(9);
		ListNode l6(9);
		ListNode l7(9);
		ListNode l8(8);

		l4.next = &l5;
		l5.next = &l6;
		l6.next = &l7;
		l7.next = &l8;

		ListNode* sum = addTwoNumbers(&l1, &l4);
		
		ListNode* first = sum;
		assert(first->val == 7);
		ListNode* second = first->next;
		assert(second->val == 9);
		ListNode* third = second->next;
		assert(third->val == 9);
		ListNode* fourth = third->next;
		assert(fourth->val == 0);
		ListNode* fifth = fourth->next;
		assert(fifth->val == 9);
		assert(fifth->next == nullptr);

		return true;
	}
};