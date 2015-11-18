#include <algorithm>
#include <vector>
#include <memory>
#include <queue>
#include <cassert>
#include <sstream>
#include <cstdlib>

using namespace std;

class ImplementStackUsingQueues
{
public:
    // Push element x onto stack.
    void push(int x) {
        if (pushUsing == 1)
        {
            queue1.push(x);
        }
        else
        {
            queue2.push(x);
        }
    }

    // Removes the element on top of the stack.
    void pop() {
        if (pushUsing == 1)
        {
            while (queue1.size() > 1)
            {
                int front = queue1.front();
                queue2.push(front);
                queue1.pop();
            }
            queue1.pop();
            pushUsing = 2;
        }
        else
        {
            while (queue2.size() > 1)
            {
                int front = queue2.front();
                queue1.push(front);
                queue2.pop();
            }
            queue2.pop();
            pushUsing = 1;
        }
    }

    // Get the top element.
    int top() {
        int top;
        int front;
        if (pushUsing == 1)
        {
            while (queue1.size() > 0)
            {
                front = queue1.front();
                queue2.push(front);
                queue1.pop();
            }
            pushUsing = 2;
            top = front;
        }
        else
        {
            while (queue2.size() > 0)
            {
                front = queue2.front();
                queue1.push(front);
                queue2.pop();
            }
            pushUsing = 1;
            top = front;
        }

        return top;
    }

    // Return whether the stack is empty.
    bool empty() {
        if (pushUsing == 1)
        {
            return queue1.empty();
        }
        else
        {
            return queue2.empty();
        }
    }

    bool Test()
    {
        ImplementStackUsingQueues stack;
        stack.push(2);
        assert(stack.top() == 2);
        stack.push(3);
        assert(stack.top() == 3);
        stack.pop();
        assert(stack.top() == 2);

        return true;
    }

private:
    queue<int> queue1;
    queue<int> queue2;
    int pushUsing = 1;
};