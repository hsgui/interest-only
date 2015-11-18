#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/search-a-2d-matrix-ii/
class Search2DMatrixII
{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int x1, int y1, int x2, int y2, int target)
    {
        if (x1 > x2 || y1 > y2)
        {
            return false;
        }

        if (x1 == x2 && y1 == y2)
        {
            return matrix[y1][x1] == target;
        }

        int mx = (x2 - x1) / 2 + x1;
        int my = (y2 - y1) / 2 + y1;
        if (matrix[my][mx] == target)
        {
            return true;
        }
        else if (matrix[my][mx] > target)
        {
            if (searchMatrix(matrix, x1, y1, x2, my - 1, target))
            {
                return true;
            }
            return searchMatrix(matrix, x1, my, mx-1, y2, target);
        }
        else
        {
            if (searchMatrix(matrix, mx + 1, y1, x2, my, target))
            {
                return true;
            }
            return searchMatrix(matrix, x1, my + 1, x2, y2, target);
        }
        return true;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0)
        {
            return false;
        }

        return searchMatrix(matrix, 0, 0, matrix[0].size()-1, matrix.size()-1, target);
    }

    bool Test()
    {
        vector<int> v1 = { 1, 4, 7, 11, 15 };
        vector<int> v2 = { 2, 5, 8, 12, 19 };
        vector<int> v3 = { 3, 6, 9, 16, 22 };
        vector<int> v4 = { 10, 13, 14, 17, 24 };
        vector<int> v5 = { 18, 21, 23, 26, 30 };

        vector<vector<int>> matrix = { v1, v2, v3, v4, v5 };
        assert(searchMatrix(matrix, 1) == true);
        assert(searchMatrix(matrix, 0) == false);
        assert(searchMatrix(matrix, 11) == true);
        assert(searchMatrix(matrix, 18) == true);
        assert(searchMatrix(matrix, 20) == false);
        assert(searchMatrix(matrix, 33) == false);
        assert(searchMatrix(matrix, 23) == true);
        assert(searchMatrix(matrix, 17) == true);

        vector<int> v6 = { 1, 1 };
        matrix = { v6 };
        assert(searchMatrix(matrix, 2) == false);
        assert(searchMatrix(matrix, 1) == true);

        v1 = { 1, 2, 3, 4, 5 };
        v2 = { 6, 7, 8, 9, 10 };
        v3 = { 11, 12, 13, 14, 15 };
        v4 = { 16, 17, 18, 19, 20 };
        v5 = { 21, 22, 23, 24, 25 };
        matrix = { v1, v2, v3, v4, v5 };
        assert(searchMatrix(matrix, 5) == true);

        return true;
    }
};