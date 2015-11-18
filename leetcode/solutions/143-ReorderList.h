#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

#include "ListNode.h"

class ReorderList{
public:
    void reorderList(ListNode * head)
    {
        // if the list contains only 0, 1, 2 elements
        if (head == NULL || head->next == NULL || head->next->next == NULL)
        {
            return;
        }

        vector<ListNode*> stack;
        ListNode* current = head;
        while (NULL != current){
            stack.push_back(current);
            current = current->next;
        }

        ListNode* forward = head;
        ListNode* backward = NULL;
        while (forward != backward && forward->next != backward)
        {
            ListNode* next = forward->next;
            backward = stack.back();
            stack.pop_back();
            forward->next = backward;
            backward->next = next;
            forward = next;
        }
        forward->next = NULL;
    }

    bool Test()
    {
        ListNode n1(1);
        ListNode n2(2);
        ListNode n3(3);
        ListNode n4(4);

        n1.next = &n2;
        n2.next = &n3;
        n3.next = &n4;

        reorderList(&n1);
        assert(n1.val == 1 && n1.next->val == 4 && n1.next->next->val == 2 && n1.next->next->next->val == 3 && n1.next->next->next->next == NULL);

        n1.next = &n2;
        n2.next = &n3;
        n3.next = NULL;
        reorderList(&n1);
        assert(n1.val == 1 && n1.next->val == 3 && n1.next->next->val == 2 && n1.next->next->next == NULL);

        return true;
    }
};