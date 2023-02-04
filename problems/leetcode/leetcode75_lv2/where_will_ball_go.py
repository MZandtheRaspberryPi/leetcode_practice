"""
You have a 2-D grid of size m x n representing a box, and you have n balls. The box is open on the top and bottom sides.

Each cell in the box has a diagonal board spanning two corners of the cell that can redirect a ball to the right or to the left.

A board that redirects the ball to the right spans the top-left corner to the bottom-right corner and is represented in the grid as 1.
A board that redirects the ball to the left spans the top-right corner to the bottom-left corner and is represented in the grid as -1.
We drop one ball at the top of each column of the box. Each ball can get stuck in the box or fall out of the bottom. A ball gets stuck if it hits a "V" shaped pattern between two boards or if a board redirects the ball into either wall of the box.

Return an array answer of size n where answer[i] is the column that the ball falls out of at the bottom after dropping the ball from the ith column at the top, or -1 if the ball gets stuck in the box.

idea:
we make a current_row var set it to 0
we then make an array of size N to track the current column location of the balls, initializing to i.
we make an array of size N to track the outcome of ball[i], initting to 0.

while current_row_var < num_rows 
  go through the outcome array, and if ball has outcome of -1 or 1, skip.
  else, if outcome not determined, look at current location wtih row var and col var, and check which direction going.
  if going right, check to see if a wall, and if not a wall check value of right cell to see if v. if v, set to -1. continue.
  else, update location of ball to be col to the right. continue to check next ball.
  
time complexity: O(nm) where n is num of balls and m is num of rows. in worst case, each ball goes all the way out
therefore, we go through m cells n times, once for each ball.

storage complexity: O(n) as we store two arrays of size n where n is number of balls.

feedback from solution:
could have done this recusively, or with dynamic programming too...


"""

from typing import List

class Solution:
    def findBall(self, grid: List[List[int]]) -> List[int]:
        if len(grid) == 0:
            return []
        num_rows: int = len(grid)
        num_cols: int = len(grid[0])
        
        current_row: int = 0
        
        outcome_array: List[int] = [0] * num_cols
        current_pos_array: List[int] = [0] * num_cols
        for i in range(num_cols):
            current_pos_array[i] = i
        
        while current_row < num_rows:
            for i in range(num_cols):
                if outcome_array[i] != 0:
                    continue # already got outcome of this ball
                ball_current_col = current_pos_array[i]
                cell_type = grid[current_row][ball_current_col]
                
                col_index_to_check: int = -1
                if cell_type == 1: # top left to bottom right
                    col_index_to_check = ball_current_col + 1
                else:
                    col_index_to_check = ball_current_col - 1
                
                if col_index_to_check < 0 or col_index_to_check >= num_cols:
                    outcome_array[i] = -1
                    continue
                elif grid[current_row][col_index_to_check] != cell_type: # ran into v
                    outcome_array[i] = -1
                    continue
                else:
                    current_pos_array[i] += cell_type
            current_row += 1
        for i in range(num_cols):
            if outcome_array[i] == 0:
                current_pos = current_pos_array[i]
                if current_pos < num_cols and current_pos >= 0:
                    outcome_array[i] = current_pos
                else:
                    outcome_array[i] = -1
        return outcome_array
                    
        
        