#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include<stdio.h>
#include<stdlib.h>
#include "random.h"

namespace algorithms{

template<typename Key, class Comparator>
class SkipList {
 private:
    struct SkipListNode;

 public:
    explicit SkipList(Comparator cmp);
    

    void Insert(const Key& key);

    bool Contains(const Key& key);

    bool Delete(const Key& key);

    void PrintList();

    void PrettyPrintList();

 private:
    SkipListNode* CreateNode(const Key& key, int level);

    bool Equal(const Key& a, const Key& b) const
    {
      return (_cmp(a, b) == 0);
    }

    int RandomLevel();

    bool KeyIsAfterNode(const Key& key, SkipListNode* node);

    SkipListNode* FindGreaterOrEqual(const Key& key, SkipListNode** previous);

    SkipListNode* FindLessThan(const Key& key);

    SkipListNode* FindLast();
    
 private:
    Comparator _cmp;

    Random _rnd;

    enum { kMaxLevel = 12 };

    SkipListNode* _head;

    SkipListNode* _tail;

    int _level;
    unsigned long _length;
};

// Implementation details
 template<typename Key, class Comparator>
  struct SkipList<Key, Comparator>::SkipListNode{

  Key key;
  struct SkipListNode* backward;
  struct SkipListNode* level[];
 };

 template<typename Key, class Comparator>
  typename SkipList<Key, Comparator>::SkipListNode*
   SkipList<Key, Comparator>::CreateNode(const Key& key, int level){
   SkipListNode* node = (SkipListNode*)malloc(sizeof(SkipListNode) + sizeof(SkipListNode *) * level);
   node->key = key;
   node->backward = NULL;
   return node;
 };

 template<typename Key, class Comparator>
   SkipList<Key, Comparator>::SkipList(Comparator cmp)
   : _cmp(cmp),
     _rnd(0xdeadbeef)
 {
   _level = 1;
   _length = 0;
   _head = CreateNode(0, kMaxLevel);
   _tail = NULL;

   _head->backward = NULL;
   for (int i = 0; i < kMaxLevel; i++){
     _head->level[i] = NULL;
   }
 };

 template<typename Key, class Comparator>
   bool 
   SkipList<Key, Comparator>::KeyIsAfterNode(const Key& key, SkipListNode* node)
   {
     return (NULL != node) && (_cmp(node->key, key) < 0);
   };

 template<typename Key, class Comparator>
   typename SkipList<Key, Comparator>::SkipListNode* 
   SkipList<Key, Comparator>::FindGreaterOrEqual(const Key& key, SkipListNode** previous)
   {
     SkipListNode* x = _head;
     SkipListNode* next = NULL;
     for (int l = _level - 1; l >= 0; l--)
     {
       next = x->level[l];
       while (KeyIsAfterNode(key, next)){
         x = next;
         next = next->level[l];
       }
       if (NULL != previous){
         previous[l] = x;
       }
     }
     return next;
   };

 template<typename Key, class Comparator>
   typename SkipList<Key, Comparator>::SkipListNode*
   SkipList<Key, Comparator>::FindLessThan(const Key& key)
   {
     return NULL;
   };

 template<typename Key, class Comparator>
   typename SkipList<Key, Comparator>::SkipListNode*
   SkipList<Key, Comparator>::FindLast()
   {
     return NULL;
   }

 template<typename Key, class Comparator>
   int
   SkipList<Key, Comparator>::RandomLevel()
   {
     static const unsigned int kBranching = 4;
     int level = 1;
     while (level < kMaxLevel && ((_rnd.Next() % kBranching) == 0)){
       level++;
     }
     return level;
   }

 template<typename Key, class Comparator>
   void 
   SkipList<Key, Comparator>::Insert(const Key& key)
   {
     SkipListNode* prev[kMaxLevel];
     SkipListNode* x = FindGreaterOrEqual(key, prev);
     if (x != NULL && _cmp(key, x->key) == 0) return;

     int level = RandomLevel();
     if (level > _level){
       for (int l = _level; l < level; l++){
         prev[l] = _head;
       }
       _level = level;
     }

     _length++;
     SkipListNode* newNode = CreateNode(key, level);
     for (int l = 0; l < level; l++){
       newNode->level[l] = prev[l]->level[l];
       prev[l]->level[l] = newNode;
     }
   };

 template<typename Key, class Comparator>
   bool
   SkipList<Key, Comparator>::Contains(const Key& key)
   {
     SkipListNode* x = FindGreaterOrEqual(key, NULL);
     return (NULL != x && Equal(x->key, key));
   };

 template<typename Key, class Comparator>
   bool
   SkipList<Key, Comparator>::Delete(const Key& key)
   {
     SkipListNode* prev[kMaxLevel];
     SkipListNode* x = FindGreaterOrEqual(key, prev);
     // didn't find the element with the key
     if (x == NULL || _cmp(key, x->key) != 0) return false;

     // update the level pointers when deleting the element with the key
     for (int l = 0; l < _level; l++){
       if (prev[l]->level[l] != x) break;
       prev[l]->level[l] = x->level[l];
     }

     // update the level of the skip list
     while (_level > 1 && _head->level[_level - 1] == NULL){
       _level--;
     }
     free(x);
     _length--;
     return true;
   };

 template<typename Key, class Comparator>
   void
   SkipList<Key, Comparator>::PrintList()
   {
     SkipListNode* currentNode = _head->level[0];
     printf("list elements are: ");
     while (currentNode != NULL){
       printf("%d ", currentNode->key);
       currentNode = currentNode->level[0];
     }
     printf("\n");
   }

 template<typename Key, class Comparator>
   void
   SkipList<Key, Comparator>::PrettyPrintList()
   {
     for (int l = _level-1; l >= 0; l--){
       printf("head-> ");
       SkipListNode* skipNode = _head->level[l];
       SkipListNode* linkNode = _head->level[0];
       for (unsigned long i = 0; i < _length; i++){
         if (linkNode != skipNode){
           printf(" \t");
           linkNode = linkNode->level[0];
         }else{
           printf("%d\t", skipNode->key);
           linkNode = linkNode->level[0];
           skipNode = skipNode->level[l];
         }
       }
       if (skipNode == linkNode && skipNode == NULL){
         printf("NULL\t");
       }
       printf("\n");
     }
   }
}

#endif
  
