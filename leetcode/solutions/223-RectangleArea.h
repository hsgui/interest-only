#include <algorithm>
#include <vector>
#include <memory>
#include <queue>
#include <cassert>
#include <sstream>
#include <cstdlib>

using namespace std;

// https://leetcode.com/problems/rectangle-area/
class RectangleArea
{
public:
    // (A, B) -> (C, D)
    // (E, F) -> (G, H)
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) 
    {
        int length1 = C - A;
        int height1 = D - B;
        int length2 = G - E;
        int height2 = H - F;

        int area1 = length1 * height1;
        int area2 = length2 * height2;

        int commonLength = 0;
        if (min(C, G) > max(A, E))
        {
            commonLength = min(C, G) - max(A, E);
        }
        int commonHeight = 0;
        if (min(D, H) > max(B, F))
        {
            commonHeight = min(D, H) - max(B, F);
        }
        int commonArea = commonHeight * commonLength;
        return area1 + area2 - commonArea;
    }

    bool Test()
    {
        int expected = 45;
        int actual = computeArea(-3, 0, 3, 4, 0, -1, 9, 2);
        assert(expected == actual);

        actual = computeArea(-1500000001, 0, -1500000000, 1, 1500000000, 0, 1500000001, 1);
        expected = 2;
        assert(actual == expected);
        return true;
    }
};