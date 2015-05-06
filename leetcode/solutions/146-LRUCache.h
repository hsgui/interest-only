#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

class LRUCache{
public:
	LRUCache(int capacity):
		m_capacity(capacity),
		m_size(0),
		head(NULL),
		tail(NULL)
	{
		m_map = make_shared<unordered_map<int, shared_ptr<DoubleNode>>>();
	}

	int get(int key)
	{
		unordered_map<int, shared_ptr<DoubleNode>>::iterator it;
		it = m_map->find(key);
		if (it == m_map->end())
		{
			return -1;
		}
		else
		{
			shared_ptr<DoubleNode> node = it->second;
			remove(node);
			update(node);

			return node->value;
		}
	}

	void set(int key, int value)
	{
		unordered_map<int, shared_ptr<DoubleNode>>::iterator it;
		it = m_map->find(key);
		if (it == m_map->end())
		{
			shared_ptr<DoubleNode> node = make_shared<DoubleNode>(key, value);
			m_map->insert({ key, node });
			if (m_size < m_capacity)
			{
				update(node);
				++m_size;
			}
			else
			{
				m_map->erase(tail->key);
				remove(tail); // tail is changed
				update(node);
			}
		}
		else
		{
			shared_ptr<DoubleNode> node = it->second;
			node->value = value;
			remove(node);
			update(node);
		}
	}

	bool Test()
	{
		LRUCache cache(2);
		cache.set(1, 1);
		cache.set(2, 2);
		assert(cache.get(1) == 1);
		assert(cache.get(2) == 2);

		cache.set(3, 3);
		assert(cache.get(1) == -1);
		assert(cache.get(3) == 3);

		LRUCache cache1(1);
		cache1.set(2, 1);
		assert(cache1.get(2) == 1);
		cache1.set(3, 2);
		assert(cache1.get(2) == -1);
		assert(cache1.get(3) == 2);

		return true;
	}

private:
	struct DoubleNode
	{
		int key;
		int value;
		shared_ptr<DoubleNode> previous;
		shared_ptr<DoubleNode> next;
		DoubleNode(int k, int v) :
			key(k),
			value(v),
			previous(NULL),
			next(NULL){}
	};

	// insert into the head of the double linked list
	void update(shared_ptr<DoubleNode> latest)
	{
		assert(NULL != latest);
		if (NULL == head)
		{
			head = latest;
			tail = latest;
		}
		else
		{
			head->previous = latest;
			latest->next = head;
			latest->previous = NULL;
			head = latest;
		}
	}

	// remove from the double linked list
	void remove(shared_ptr<DoubleNode> latest)
	{
		assert(NULL != latest);
		if (latest != head && latest != tail)
		{
			latest->previous->next = latest->next;
			latest->next->previous = latest->previous;
		}

		if (head == latest)
		{
			head = head->next;
			if (NULL != head)
			{
				head->previous = NULL;
			}
		}
		if (tail == latest)
		{
			tail = tail->previous;
			if (NULL != tail)
			{
				tail->next = NULL;
			}
		}

		latest->next = NULL;
		latest->previous = NULL;
	}

	shared_ptr<DoubleNode> head;
	shared_ptr<DoubleNode> tail;
	int m_capacity;
	int m_size;

	shared_ptr<unordered_map<int, shared_ptr<DoubleNode>>> m_map;
};