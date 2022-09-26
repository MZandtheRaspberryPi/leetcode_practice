#include <algorithm>

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
      // exemplify
      // indices 0, 0 0, 1  0 2 0,3  1, 3  2, 3 2 2 
        
        
     // increase col till , increase row, decrease col, decrease row till greater than start
     // set ending pos col to n
     // set ending pos row to m
     // set ending neg col to 0
    // set ending neg row to  0 + 1
     
    // int starting m int starting n = 0 0
    // while true, for int i = starting n < ending n i ++, add to vector matrix[m][n]
     // then for pos row
     // then for neg col
    // then for neg row
    // then decrement pos ones by 1, increment neg ones by 1.
        
   // O(N) in time, O(1) in space. But is the matrix guaranteed to be increasing? if so, perhaps something more clever.
        
        // handle zero inputs
        
        std::vector<int> result;
        
       int ending_pos_col = matrix[0].size();
       int ending_pos_row = matrix.size();
       int ending_neg_col = 0;
       int ending_neg_row = 0;
       
       while (true)
       {
           // move left to right in top row
           if (ending_pos_col > ending_neg_col)
           {
               for (int i = ending_neg_col; i < ending_pos_col; i++)
               {
                   result.push_back(matrix[ending_neg_row][i]);
               }
           }
           else
           {
               break;
           }
           
           // move up to down in right side
           if (ending_pos_row - 1> ending_neg_row)
           {
               for (int i = ending_neg_row + 1; i < ending_pos_row; i++)
               {
                   result.push_back(matrix[i][ending_pos_col - 1]);
               }
           }
           else
           {
               break;
           }
           
           // move right to left in bottom row
           if (!(ending_neg_col == ending_pos_col - 1))
           {
               for (int i = ending_pos_col - 1 - 1; i >= ending_neg_col; i--)
               {
                   result.push_back(matrix[ending_pos_row - 1][i]);
               }
           }
           else
           {
               break;
           }
           
           // move down to up in left side
           if (!(ending_neg_row == ending_pos_row - 1 -1))
           {
               for (int i = ending_pos_row - 1 - 1; i > ending_neg_row; i--)
               {
                   result.push_back(matrix[i][ending_neg_row]);
               }
           }
           else
           {
               break;
           }
           
           ending_pos_col--;
           ending_pos_row--;
           ending_neg_col++;
           ending_neg_row++;
           
       }
        
        return result;
        
    }
};
