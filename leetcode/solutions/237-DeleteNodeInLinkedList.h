#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

#include "ListNode.h"

using namespace std;

//https://leetcode.com/problems/delete-node-in-a-linked-list/
class DeleteNodeInLinkedList
{
public:
    // change the value 
    void deleteNode(ListNode* node) {
        ListNode* next = node->next;
        assert(next != nullptr);
        node->val = next->val;
        node->next = next->next;
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

        deleteNode(&l2);
        assert(l1.next->val == 3);

        deleteNode(&l1);
        assert(l1.val == 3);
        assert(l1.next->val == 4);
        return true;
    }
};