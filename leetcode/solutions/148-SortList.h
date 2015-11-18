#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

#include "ListNode.h"

// https://leetcode.com/problems/sort-list/
class SortList
{
public:
    // O(n * log(n))
    ListNode* sortList(ListNode* head)
    {
        if (head == NULL)
        {
            return head;
        }

        int length = 1;
        ListNode* current = head;
        for (length = 1; current->next != NULL; ++length, current = current->next);

        ListNode* tail;
        return sortList(head, 0, length - 1, tail);
    }
    ListNode* sortList(ListNode* head, int start, int end, ListNode* & tail)
    {
        if (start >= end)
        {
            tail = head;
            return head;
        }
        else
        {
            int middle = (end - start) / 2 + start;
            ListNode* leftTail;
            ListNode* rightTail;

            ListNode* listA = sortList(head, start, middle, leftTail);
            ListNode* listB = sortList(leftTail->next, middle + 1, end, rightTail);
            
            ListNode* next = rightTail->next;
            leftTail->next = NULL;
            rightTail->next = NULL;
            // merge
            ListNode dump(0);
            ListNode* current = &dump;
            ListNode* currentNodeInA = listA;
            ListNode* currentNodeInB = listB;
            while (currentNodeInA != NULL && currentNodeInB != NULL)
            {
                // either currentNodeInA or currentNodeInB is changed
                if (currentNodeInA->val <= currentNodeInB->val)
                {
                    current->next = currentNodeInA;
                    current = currentNodeInA;
                    currentNodeInA = currentNodeInA->next;
                }
                else
                {
                    current->next = currentNodeInB;
                    current = currentNodeInB;
                    currentNodeInB = currentNodeInB->next;
                }
            }

            assert(currentNodeInA != NULL || currentNodeInB != NULL);

            if (currentNodeInA == NULL)
            {
                current->next = currentNodeInB;
                tail = rightTail;
            }
            else if (currentNodeInB == NULL)
            {
                current->next = currentNodeInA;
                tail = leftTail;
            }
            tail->next = next;

            return dump.next;
        }
    }

    bool Test()
    {
        ListNode l1(1);
        ListNode l2(2);
        ListNode l3(3);
        ListNode l4(4);

        l1.next = &l3;
        l3.next = &l2;
        l2.next = &l4;

        ListNode* head = sortList(&l1);
        for (int i = 1; head != NULL; head = head->next, ++i)
        {
            assert(head->val == i);
        }

        l4.next = NULL;
        head = sortList(&l4);
        assert(head->val == 4);
        assert(head->next == NULL);
        
        return true;
    }
};