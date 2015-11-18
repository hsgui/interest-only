#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

class UniqueBinarySearchTrees{
public:
    int numTrees(int n) 
    {
        int num = 0;
        if (n <= 0)
        {
            return num;
        }
        // another way to declare this:
        // shared_ptr<int> nums(new int[n], default_delete<int[]>());
        // cite: http://stackoverflow.com/questions/13061979/shared-ptr-to-an-array-should-it-be-used
        shared_ptr<int> nums(new int[n+1], [](int *p) {delete[] p; });

        // nums[n] = sum_{i=0}^{n-1}(nums[i] * nums[n - i - 1])
        // this is Catalan Number.
        (nums.get())[0] = 1;
        (nums.get())[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            num = 0;
            for (int j = 0; j < i; ++j)
            {
                num += nums.get()[j] * nums.get()[i - j - 1];
            }
            nums.get()[i] = num;
        }
        return nums.get()[n];
    }

    bool Test()
    {
        int expected = 5;
        int actual = numTrees(3);
        assert(expected == actual);
        
        return true;
    }
};