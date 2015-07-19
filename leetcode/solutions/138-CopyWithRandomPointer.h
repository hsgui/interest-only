#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

#include "ListNode.h"

using namespace std;

// https://leetcode.com/problems/copy-list-with-random-pointer/
class CopyWithRandomPointer
{
public:
	// original linked list
	//	next:				1 -> 2 -> 3 -> 4 -> 5
	//	random:				1 ------> 3
	//	random:				2 <- 3
	// copied linked list:
	// next:				1 -> 2 -> 3 -> 4 -> 5
	// random:				copied node 1 -> the random pointer of original node 1
	// random:				original node 1 -> copied node 1 => one to one
	RandomListNode *copyRandomList(RandomListNode *head) 
	{
		RandomListNode* copiedListHead = nullptr;
		if (head == nullptr)
		{
			return nullptr;
		}

		RandomListNode* currentNode = head;
		RandomListNode* copiedCurrentNode = nullptr;
		RandomListNode* copiedPreviousNode = nullptr;

		// copy the next pointer
		while (currentNode != nullptr)
		{
			RandomListNode* copiedCurrentNode = new RandomListNode(currentNode->label);

			// hack
			// use the copiedCurrentNode->next to store more useful information
			copiedCurrentNode->random = currentNode->random;
			currentNode->random = copiedCurrentNode;

			currentNode = currentNode->next;

			// link the next of copied link list
			if (copiedListHead == nullptr)
			{
				copiedListHead = copiedCurrentNode;
			}
			else
			{
				copiedPreviousNode->next = copiedCurrentNode;
			}

			copiedPreviousNode = copiedCurrentNode;
		}

		// link the random pointer
		currentNode = head;
		while (currentNode != nullptr)
		{
			RandomListNode* copiedNode = currentNode->random;
			RandomListNode* randomPointerToOriginal = copiedNode->random;
			if (randomPointerToOriginal == nullptr)
			{
				copiedNode->random = nullptr;
				// restore the original node's random pointer -- cann't restore here!
				currentNode->random = nullptr;
			}
			else
			{
				copiedNode->random = randomPointerToOriginal->random;
				// restore the original node's random pointer
				currentNode->random = randomPointerToOriginal;
			}

			currentNode = currentNode->next;
		}

		return copiedListHead;
	}

	bool Test()
	{
		RandomListNode n1(1);
		RandomListNode n2(2);
		RandomListNode n3(3);
		RandomListNode n4(4);
		RandomListNode n5(5);

		n1.next = &n2, n1.random = &n3;
		n2.next = &n3, n2.random = &n1;
		n3.next = &n4;
		n4.next = &n5;
		n5.random = &n4;

		RandomListNode* copied = copyRandomList(&n1);
		assert(copied->label == 1);
		assert(copied->random->label == 3);

		RandomListNode* copied2 = copied->next;
		assert(copied2->label == 2);
		assert(copied2->random->label == 1);

		RandomListNode* copied3 = copied2->next;
		assert(copied3->label == 3);
		assert(copied3->random == nullptr);

		RandomListNode* copied4 = copied3->next;
		assert(copied4->label == 4);
		assert(copied4->random == nullptr);

		RandomListNode* copied5 = copied4->next;
		assert(copied5->label == 5);
		assert(copied5->random->label == 4);

		RandomListNode n6(6);
		
		copied = copyRandomList(&n6);
		assert(copied->label == 6);
		assert(copied->random == nullptr);
		assert(copied->next == nullptr);

		return true;
	}
};