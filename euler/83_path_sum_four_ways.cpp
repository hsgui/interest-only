#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<vector>
#include<utility>

class Item{
public:
  int priority;
  int row;
  int column;

  Item(int priority, int row, int column):
    priority(priority),
    row(row),
    column(column){}
};

class ItemComparer{
public:
  bool operator() (const Item& l, const Item& r) const{
    return l.priority > r.priority;
  }
};

/*
  https://projecteuler.net/problem=82
 */
void PathSumFourWays_83()
{
  int row = 80, column = 80;
  int i, j;
  int matrix[row][column];

  // read data from file
  for (i=0; i < row; i++)
    for (j = 0; j < column; j++){
      if (j < column - 1)
        scanf("%d,", &matrix[i][j]);
      else
        scanf("%d", &matrix[i][j]);
    }

  // initial all values to undefined;
  int minimal[row][column];
  for (i = 0; i < row; i++){
    for (j = 0; j < column; j++){
      minimal[i][j] = -1;
    }
  }

  std::priority_queue<Item, std::vector<Item>, ItemComparer> pq;

  Item start(matrix[0][0], 0, 0);
  Item end(-1, row-1, column-1);

  minimal[start.row][start.column] = matrix[start.row][start.column];
  pq.push(start);

  int priority;
  std::pair<int, int> direction;
  std::vector<std::pair<int, int>> directions;

  std::pair<int, int> up(0, -1);
  std::pair<int, int> down(0, 1);
  std::pair<int, int> left(-1, 0);
  std::pair<int, int> right(1, 0);

  directions.push_back(up);
  directions.push_back(down);
  directions.push_back(left);
  directions.push_back(right);

  while (!pq.empty()){
    Item item = pq.top();
    pq.pop();
    if (item.row == end.row && item.column == end.column) break;

    for (std::vector<std::pair<int, int>>::iterator it = directions.begin(); 
         it != directions.end(); it++){
      direction = *it;
      int r = item.row + direction.first;
      int c = item.column + direction.second;
      if (r >=0 && r < row && c >= 0 && c < column){
        priority = item.priority + matrix[r][c];
        // if the point is not seem ever or has larger priority
        if (minimal[r][c] == -1 ||
            minimal[r][c] > priority){
          minimal[r][c] = priority;
          Item i(priority, r, c);
          // same items with different priorities may exist in pq;
          // but it will affect the final result
          pq.push(i); 
        }
      }
    }
  }
  printf("%d\n", minimal[end.row][end.column]);
}

int main()
{
  PathSumFourWays_83();
}
