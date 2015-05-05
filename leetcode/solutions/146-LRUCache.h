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
			shared_ptr<DoubleNode> node = make_shared<DoubleNode>(value);
			m_map->insert({ key, node });
			if (m_size < m_capacity)
			{
				update(node);
				++m_size;
			}
			else
			{
				// todo remove element from the unordered_map
				remove(tail);
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

		return true;
	}

private:
	struct DoubleNode
	{
		int value;
		shared_ptr<DoubleNode> previous;
		shared_ptr<DoubleNode> next;
		DoubleNode(int v) :
			value(v),
			previous(NULL),
			next(NULL){}
	};

	void update(shared_ptr<DoubleNode>& latest)
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

	void remove(shared_ptr<DoubleNode>& latest)
	{
		assert(NULL != latest);
		if (head == latest)
		{
			head = latest->next;
			if (NULL != head)
			{
				head->previous = NULL;
			}
		}
		if (tail == latest)
		{
			tail = latest->previous;
			if (NULL != tail)
			{
				tail->next = NULL;
			}
		}
		if (latest != head && latest != tail)
		{
			latest->previous->next = latest->next;
			latest->next->previous = latest->previous;
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