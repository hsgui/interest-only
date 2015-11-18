#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"
#include "ListNode.h"

using namespace std;

// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
class ConvertSortedListToBinarySearchTree
{
public:
    TreeNode* sortedListToBST(ListNode* head)
    {
        if (head == NULL)
        {
            return NULL;
        }

        int length = 0;
        for (ListNode* current = head; current != NULL; current = current->next, ++length);

        TreeNode* root = NULL;
        ListNode* tail = NULL;
        sortedListToBST(head, 0, length - 1, tail, root);
        return root;
    }

    void sortedListToBST(ListNode* head, int start, int end, ListNode* & tail, TreeNode* & root)
    {
        if (start > end)
        {
            tail = NULL;
            root = NULL;
        }
        else
        {
            int middle = (end - start) / 2 + start;
            TreeNode* leftRoot = NULL, *rightRoot = NULL;
            ListNode* leftTail = NULL, *rightTail = NULL;
            sortedListToBST(head, start, middle - 1, leftTail, leftRoot);
            if (leftTail == NULL)
            {
                root = new TreeNode(head->val);

                tail = head;
                head = head->next;
            }
            else
            {
                root = new TreeNode(leftTail->next->val);
                root->left = leftRoot;

                tail = leftTail->next;
                head = leftTail->next->next;
            }
            sortedListToBST(head, middle + 1, end, rightTail, rightRoot);
            root->right = rightRoot;

            if (rightTail != NULL)
            {
                tail = rightTail;
            }
        }
    }

    bool Test()
    {
        TreeNode* root;
        assert(sortedListToBST(NULL) == NULL);

        ListNode l1(1);
        ListNode l2(2);
        ListNode l3(3);
        
        l1.next = &l2;
        l2.next = &l3;

        root = sortedListToBST(&l1);
        assert(root->val == 2 && root->left->val == 1 && root->right->val == 3);

        l2.next = NULL;
        root = sortedListToBST(&l1);
        assert(root->val == 1 && root->right->val == 2);

        return true;
    }
};