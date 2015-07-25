#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>
#include <cassert>

#include "TreeNode.h"

using namespace std;

// https://leetcode.com/problems/clone-graph/
class CloneGraph
{
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) 
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		queue<UndirectedGraphNode*> originalGraphQueue;
		
		unordered_map<int, UndirectedGraphNode*> labelToCloneNodeMap;

		UndirectedGraphNode* cloneGraphRoot = new UndirectedGraphNode(node->label);

		UndirectedGraphNode* currentNodeInOriginalGraph = node;
		UndirectedGraphNode* currentNodeInCloneGraph = cloneGraphRoot;

		originalGraphQueue.push(currentNodeInOriginalGraph);
		
		labelToCloneNodeMap.insert({ node->label, cloneGraphRoot });

		while (!originalGraphQueue.empty())
		{
			currentNodeInOriginalGraph = originalGraphQueue.front();
			originalGraphQueue.pop();

			currentNodeInCloneGraph = labelToCloneNodeMap[currentNodeInOriginalGraph->label];
			for (auto neighbor : currentNodeInOriginalGraph->neighbors)
			{
				auto it = labelToCloneNodeMap.find(neighbor->label);
				if (it == labelToCloneNodeMap.end())
				{
					UndirectedGraphNode* cloneNeighbor = new UndirectedGraphNode(neighbor->label);

					labelToCloneNodeMap.insert({ cloneNeighbor->label, cloneNeighbor });

					originalGraphQueue.push(neighbor);
				}
				currentNodeInCloneGraph->neighbors.push_back(labelToCloneNodeMap[neighbor->label]);
			}
		}
		return cloneGraphRoot;
	}

	bool Test()
	{
		assert(cloneGraph(nullptr) == nullptr);

		UndirectedGraphNode n1(1);
		UndirectedGraphNode* clone = cloneGraph(&n1);
		assert(clone->label == 1 && clone->neighbors.size() == 0);

		n1.neighbors.push_back(&n1);
		clone = cloneGraph(&n1);
		assert(clone->label == 1 && clone->neighbors.size() == 1 && clone->neighbors[0]->label == 1);

		UndirectedGraphNode n2(2);
		UndirectedGraphNode n3(3);
		n1.neighbors.push_back(&n2);
		n1.neighbors.push_back(&n3);

		n2.neighbors.push_back(&n3);
		n3.neighbors.push_back(&n2);

		clone = cloneGraph(&n1);
		assert(clone->label == 1 && clone->neighbors.size() == 3);
		assert(clone->neighbors[0]->label == 1 && clone->neighbors[1]->label == 2 && clone->neighbors[2]->label == 3);

		UndirectedGraphNode* clone2 = clone->neighbors[1];
		UndirectedGraphNode* clone3 = clone->neighbors[2];
		assert(clone2->neighbors.size() == 1 && clone2->neighbors[0]->label == 3);
		assert(clone3->neighbors.size() == 1 && clone3->neighbors[0]->label == 2);

		return true;
	}
};