#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

#include "ListNode.h"

// https://leetcode.com/problems/remove-linked-list-elements/
class RemoveLinkedListElements
{
public:
    ListNode* removeElements(ListNode* head, int val) 
    {
        // dump node, reduce some checkpoints
        ListNode dump(0);
        dump.next = head;

        ListNode* current = &dump;
        while (current->next != NULL)
        {
            if (current->next->val == val)
            {
                current->next = current->next->next;
            }
            else
            {
                current = current->next;
            }
        }
        return dump.next;
    }

    bool Test()
    {
        ListNode l1(1);
        ListNode l1_1(1);
        assert(removeElements(NULL, 1) == NULL);
        assert(removeElements(&l1, 1) == NULL);
        l1.next = &l1_1;
        assert(removeElements(&l1, 1) == NULL);

        l1.next = new ListNode(2);
        assert(removeElements(&l1, 1)->val == 2);

        return true;
    }
};