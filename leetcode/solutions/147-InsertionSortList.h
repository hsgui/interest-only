#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

#include "ListNode.h"

// https://leetcode.com/problems/insertion-sort-list/
class InsertionSortList
{
public:
    ListNode* insertionSortList(ListNode* head) 
    {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }

        ListNode dumpNode(0);
        dumpNode.next = head;

        ListNode* current = head->next;
        head->next = NULL;
        while (current != NULL)
        {
            ListNode* biggestLess = &dumpNode;
            while (biggestLess->next != NULL 
                && biggestLess->next->val < current->val)
            {
                biggestLess = biggestLess->next;
            }
            ListNode* next = current->next;
            current->next = biggestLess->next;
            biggestLess->next = current;
            current = next;
        }

        return dumpNode.next;
    }

    bool Test()
    {
        ListNode l1(11);
        assert(insertionSortList(NULL) == NULL);
        assert(insertionSortList(&l1) == &l1);

        ListNode* current = &l1;
        for (int i = 10; i > 1; --i)
        {
            current->next = new ListNode(i);
            current = current->next;
        }

        ListNode* sortedList = insertionSortList(&l1);
        for (int i = 2; i <= 11; ++i)
        {
            assert(sortedList != NULL);
            assert(sortedList->val == i);
            sortedList = sortedList->next;
        }

        assert(sortedList == NULL);

        ListNode l2(2);
        ListNode l3(3);
        ListNode l4(4);
        l3.next = &l2;
        l2.next = &l4;
        sortedList = insertionSortList(&l3);
        assert(sortedList->val == 2);
        assert(sortedList->next->val == 3);
        assert(sortedList->next->next->val == 4);
        assert(sortedList->next->next->next == NULL);

        return true;
    }
};