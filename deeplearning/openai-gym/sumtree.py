# https://jaromiru.com/2016/11/07/lets-make-a-dqn-double-learning-and-prioritized-experience-replay/
# https://github.com/jaara/AI-blog/blob/master/SumTree.py

import numpy as np

class SumTree:
    write = 0
    isFull = False

    def __init__(self, capacity):
        '''
        for a binary tree, we have:
        n0 = n2 + 1: n0 is the leaf node
        for a complete binary tree, n1 = 0 or 1
        but for our case, n1 is always 0 (consider the leaf node).
        That is, we will only have nodes with 2 children or none
        when n1 is 1, we could always remove the last leaf node, 
        and the parent of this leaf node will become a leaf node.
        So the leaf node index of this complete binary tree is:
        [ capacity - 1, 2 * capacity -2]
        '''
        self.capacity = capacity
        self.tree = np.zeros(2 * capacity - 1)
        self.data = np.zeros(capacity, dtype=object)

    def _propagate(self, idx, change):
        parent = (idx - 1) // 2

        self.tree[parent] += change
        if parent != 0:
            self._propagate(parent, change)

    def _retrieve(self, idx, s):
        left = 2 * idx + 1
        right = left + 1

        if left >= len(self.tree):
            return idx

        if s <= self.tree[left]:
            return self._retrieve(left, s)
        else:
            return self._retrieve(right, s - self.tree[left])

    def total(self):
        return self.tree[0]

    def add(self, p, data):
        self.data[self.write] = data

        idx = self.write + self.capacity - 1
        self.update(idx, p)
        
        self.write += 1
        if self.write >= self.capacity:
            self.write = 0
            self.isFull = True

    def update(self, idx, p):
        change = p - self.tree[idx]

        self.tree[idx] = p
        self._propagate(idx, change)

    def get(self, s):
        # the index of leaf node in the tree
        idx = self._retrieve(0, s)
        dataIdx = idx - self.capacity + 1

        return (idx, self.tree[idx], self.data[dataIdx])

    def isFull(self):
        return self.isFull
