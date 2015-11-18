#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

//https://leetcode.com/problems/search-a-2d-matrix/
class Search2DMatrix
{
public:
    int getValueInMatrix(vector<vector<int>>& matrix, int position)
    {
        int column = matrix[0].size();

        int rowIndex = position / column;
        int columnIndex = position % column;

        return matrix[rowIndex][columnIndex];
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0)
        {
            return false;
        }

        int row = matrix.size();
        int column = matrix[0].size();

        int low = 0;
        int high = row * column - 1;

        while (low < high)
        {
            int middle = (high - low) / 2 + low;
            if (getValueInMatrix(matrix, middle) == target)
            {
                return true;
            }
            if (getValueInMatrix(matrix, middle) < target)
            {
                low = middle + 1;
            }
            else
            {
                high = middle - 1;
            }
        }

        if (getValueInMatrix(matrix, low) == target) return true;
        return false;
    }

    bool Test()
    {
        vector<vector<int>> matrix;
        vector<int> row1 = { 1, 3, 5, 7 };
        vector<int> row2 = { 10, 11, 16, 20 };
        vector<int> row3 = { 23, 30, 34, 50 };
        vector<int> row4 = { 53, 55, 57, 60 };
        matrix = { row1, row2, row3, row4 };

        assert(searchMatrix(matrix, 1) == true);
        assert(searchMatrix(matrix, 0) == false);
        assert(searchMatrix(matrix, 2) == false);
        assert(searchMatrix(matrix, 7) == true);
        assert(searchMatrix(matrix, 9) == false);
        assert(searchMatrix(matrix, 70) == false);
        assert(searchMatrix(matrix, 60) == true);
        assert(searchMatrix(matrix, 56) == false);
        return true;
    }
};