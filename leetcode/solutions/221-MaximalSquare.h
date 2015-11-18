#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/maximal-square/
class MaximalSquare
{
public:
    int maximalSquare(vector<vector<char>>& matrix) 
    {
        vector<vector<int>> maxSquare;
        int maxSquareSoFar = 0;

        // allocate memory
        int row = matrix.size();
        if (row == 0)
        {
            return 0;
        }
        int column = matrix[0].size();
        if (column == 0)
        {
            return 0;
        }

        maxSquare.reserve(row);
        for (int i = 0; i < row; ++i)
        {
            vector<int> v;
            v.resize(column);
            maxSquare.push_back(v);
        }

        for (int i = 0; i < row; ++i)
        {
            if (matrix[i][0] == '1')
            {
                maxSquare[i][0] = 1;
                maxSquareSoFar = 1;
            }
            else
            {
                maxSquare[i][0] = 0;
            }
        }

        for (int j = 0; j < column; ++j)
        {
            if (matrix[0][j] == '1')
            {
                maxSquare[0][j] = 1;
                maxSquareSoFar = 1;
            }
            else
            {
                maxSquare[0][j] = 0;
            }
        }

        for (int i = 1; i < row; ++i)
        {
            for (int j = 1; j < column; ++j)
            {
                if (matrix[i][j] == '1')
                {
                    maxSquare[i][j] = min(min(maxSquare[i - 1][j - 1], maxSquare[i - 1][j]), maxSquare[i][j - 1]) + 1;
                    if (maxSquare[i][j] > maxSquareSoFar)
                    {
                        maxSquareSoFar = maxSquare[i][j];
                    }
                }
                else
                {
                    maxSquare[i][j] = 0;
                }
            }
        }

        return maxSquareSoFar * maxSquareSoFar;
    }

    bool Test()
    {
        vector<vector<char>> matrix;
        vector<char> v1 = { '1', '0', '1', '0', '0' };
        vector<char> v2 = { '1', '0', '1', '1', '1' };
        vector<char> v3 = { '1', '1', '1', '1', '1' };
        vector<char> v4 = { '1', '0', '0', '1', '0' };
        matrix.push_back(v1);
        matrix.push_back(v2);
        matrix.push_back(v3);
        matrix.push_back(v4);
        
        assert(maximalSquare(matrix) == 2*2);
        return true;
    }
};