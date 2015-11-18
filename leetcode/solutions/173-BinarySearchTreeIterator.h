#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "TreeNode.h"
#include "108-ConvertSortedArrayToBinarySearchTree.h"

using namespace std;

// https://leetcode.com/problems/binary-search-tree-iterator/
class BSTIterator {
public:
    BSTIterator(): 
        m_root(NULL),
        m_next(NULL)
    {
        m_rootStack.clear();
    }

    BSTIterator(TreeNode *root) 
    {
        m_root = root;
        m_next = root;
        m_rootStack.clear();
        if (m_next != NULL)
        {
            while (m_next->left != NULL)
            {
                m_rootStack.push_back(m_next);
                m_next = m_next->left;
            }
            m_rootStack.push_back(m_next);
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return m_next != NULL;
    }

    /** @return the next smallest number */
    int next() {
        assert(m_next != NULL);
        int value = m_next->val;

        TreeNode* previous = m_next;
        if (!m_rootStack.empty())
        {
            TreeNode* top = m_rootStack.back();
            assert(top == previous);
            if (top->right != NULL)
            {
                m_next = top->right;
                while (m_next->left != NULL)
                {
                    m_rootStack.push_back(m_next);
                    m_next = m_next->left;
                }
                m_rootStack.push_back(m_next);
            }
            else
            {
                m_rootStack.pop_back();
                if (!m_rootStack.empty())
                {
                    top = m_rootStack.back();
                    while (top->right == previous && !m_rootStack.empty())
                    {
                        previous = top;
                        m_rootStack.pop_back();
                        if (!m_rootStack.empty())
                        {
                            top = m_rootStack.back();
                        }
                    }
                }

                if (m_rootStack.empty())
                {
                    m_next = NULL;
                }
                else if (top->left == previous)
                {
                    m_next = top;
                }
            }
        }
        else
        {
            m_next = NULL;
        }

        return value;
    }

    bool Test()
    {
        vector<int> nums;
        for (int i = 1; i < 2; ++i)
        {
            nums.push_back(i);
        }

        ConvertSortedArrayToBinarySearchTree converter;
        TreeNode* root = converter.sortedArrayToBST(nums);

        BSTIterator it = BSTIterator(root);

        for (int i = 1; it.hasNext(); ++i)
        {
            assert(i == it.next());
        }

        return true;
    }

private:
    TreeNode* m_root;
    TreeNode* m_next;

    vector<TreeNode*> m_rootStack;
};