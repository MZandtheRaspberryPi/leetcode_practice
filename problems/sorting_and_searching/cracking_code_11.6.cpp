/*
Given an MxM matrix, in which each row and column is sorted, write a method to find an element.

Example: search(matrix, 7) -> std::pair 2, 0

1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25


search rows first. binary search, pick middle and outer indices.  if search number is less than or equal to matrix[mid][M] and greater than or equal to matrix[mid][0], select mid for row.
if search num less than mid  and greater or equal to  matrix[low][0] then search low. if search is greater than mid and less than or equal to matrix[high][M] search higher part.

once have row index, that row for col index in typical binary search.

This would operate in o(logn). and similar storage as recursion stores in stack.

Another idea is to try and use gradient descent here. If we pick the middle element of matrix, and calculate the difference between our target and the middle. Then make that calculation for each of the 4
elements around the middle. From here, we take the difference between the difference of mid, and difference of its surroundings and move in the direction that is the most negative. We do this until we 
find our number.
This should run in O(M^2). constant storage.


*/

#include<vector>
#include <stdio.h>
// Need type T that can go negative, todo, check for that

enum MatrixNeighbor
{
  UPPER,
  LOWER,
  LEFT,
  RIGHT,
  TOP_LEFT,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT
};


template<typename T>
std::pair<T, T> calcNewIndices(std::pair<T, T>& middle_index, MatrixNeighbor& neighbor)
{

  std::pair<T, T> neighbor_indices;

 switch(neighbor)
  {
     case UPPER:
       neighbor_indices.first = middle_index.first - 1;
       neighbor_indices.second = middle_index.second;
       break;
     case LOWER:
       neighbor_indices.first = middle_index.first + 1;
       neighbor_indices.second = middle_index.second;
       break;
     case LEFT:
       neighbor_indices.first = middle_index.first;
       neighbor_indices.second = middle_index.second - 1;
       break;
     case RIGHT:
       neighbor_indices.first = middle_index.first;
       neighbor_indices.second = middle_index.second + 1;
       break;
     case TOP_LEFT:
       neighbor_indices.first = middle_index.first - 1;
       neighbor_indices.second = middle_index.second - 1;
       break;
     case TOP_RIGHT:
       neighbor_indices.first = middle_index.first - 1;
       neighbor_indices.second = middle_index.second + 1;
       break;
     case BOTTOM_LEFT:
       neighbor_indices.first = middle_index.first + 1;
       neighbor_indices.second = middle_index.second - 1;
       break;
     case BOTTOM_RIGHT:
       neighbor_indices.first = middle_index.first + 1;
       neighbor_indices.second = middle_index.second + 1;
       break;
     default:
       break;
  }

  return neighbor_indices;

}


template <typename T>
T calcDiffFromGoal(std::vector<std::vector<T>>& matrix, T& search_val, T& middle_difference_from_search_val, std::pair<T, T>& middle_index, MatrixNeighbor& neighbor)
{

  T difference_from_search_val;
  std::pair<T, T> neighbor_indices;

  neighbor_indices = calcNewIndices(middle_index, neighbor);

  if (neighbor_indices.first > matrix.size() - 1 || neighbor_indices.second > matrix.size() - 1)
  {
     neighbor_indices = middle_index;
  }

  difference_from_search_val = search_val - matrix[neighbor_indices.first][neighbor_indices.second];
  return difference_from_search_val;
}

template<typename T>
T abs(T val)
{
  if (val < 0)
  {
     return val * -1;
  }
  else
   {
     return val;
   }
}

template <typename T>
std::pair<T, T> searchMatrix(std::vector<std::vector<T>> matrix, T search_val)
{

    std::pair<T, T> result;
    std::pair<T, T> middle_indices;
    middle_indices.first = matrix.size() / 2;
    middle_indices.second = middle_indices.first;
    // upper, lower, left, right
    std::vector<T> neighbor_array(8);
    T mid;
    while(true)
    {
        printf("searching %d\n", matrix[middle_indices.first][middle_indices.second]);
        if (matrix[middle_indices.first][middle_indices.second] == search_val)
        {
            break;
        }
        mid = search_val - matrix[middle_indices.first][middle_indices.second];

        for (int i = 0; i < neighbor_array.size(); i++)
        {
           MatrixNeighbor current_neighbor = static_cast<MatrixNeighbor>(i);
           neighbor_array[current_neighbor] =   calcDiffFromGoal(matrix, search_val, mid, middle_indices, current_neighbor);
        }

        T best_move_index;
        T best_move = abs(mid);
        for (int i = 0; i < neighbor_array.size(); i++)
        {
           if (abs(neighbor_array[i]) < best_move)
           {
              best_move_index = i;
              best_move = neighbor_array[i];
           }
        }
        MatrixNeighbor best_move_neighbor_type = static_cast<MatrixNeighbor>(best_move_index);
        middle_indices = calcNewIndices(middle_indices, best_move_neighbor_type);
    }
    return middle_indices;
}

void printMatrix(std::vector<std::vector<int>> matrix)
{

  for (int i = 0; i < matrix.size(); i ++)
  {
    for (int j = 0; j < matrix[0].size(); j ++)
    {
       printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

}


template<typename T>
bool searchMatrixOptimal(std::vector<std::vector<T>> matrix, T search_val)
{

  // if start of a column is greater than x, x must be to the right of that column
  // if end of a row is less than x, x must be below that row.
  std::pair<T, T> result;
  result.first = 0;
  result.second = matrix[0].size() - 1;
  
  while (result.first < matrix.size() && result.second >= 0)
  {
    if (matrix[result.first][result.second] == search_val)
    {
      return true;
    }
    else if (matrix[result.first][result.second] > search_val)
    {
      result.second --;
    }
    else
    {
      result.first++;
    }
  }

  return false;

}


int main()
{
  std::vector<std::vector<int>> matrix;
  int M = 10;
  matrix.resize(M);


  for (int i = 0; i < 10; i ++)
  {
    matrix[i].resize(M);
    for (int j = 0; j < M; j ++)
    {
       matrix[i][j] = i * 10 + j;
    }
  }

  printMatrix(matrix);

  std::pair<int, int> result = searchMatrix(matrix, 33);
  printf("found 33 at %d, %d\n", result.first, result.second);

  result = searchMatrix(matrix, 74);
  printf("found 74 at %d, %d\n", result.first, result.second);

  bool found = searchMatrixOptimal(matrix, 23);
  printf("found %d\n", found);

}
