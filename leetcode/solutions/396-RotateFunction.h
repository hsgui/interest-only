#pragma once

#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class RotateFunction
{
public:
    int maxRotateFunction(vector<int>& A) {
        // f(i) = f(i-1) + sum(A) - n * A[n-i]
        int f0 = 0;
        int sum = 0;
        for (int i = 0; i < A.size(); ++i)
        {
            sum += A[i];
            f0 += i * A[i];
        }

        int result = f0;
        int fprevious = f0;
        for (int i = 1; i < A.size(); i++)
        {
            int fi = fprevious + sum - A.size() * A[A.size() - i];
            result = max(result, fi);

            fprevious = fi;
        }

        return result;
    }

    bool Test()
    {
        vector<int> c1 = { 4, 3, 2, 6 };
        assert(maxRotateFunction(c1) == 26);

        return true;
    }
};