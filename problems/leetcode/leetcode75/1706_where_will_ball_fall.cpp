class Solution {
public:
    
    bool isAtVJunction(const int& col_index, const int& row_index, const std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        
        bool at_v_junction = false;
        if (col_index >= 0 && col_index < n - 1)
        {
            at_v_junction |= (grid[row_index][col_index] == 1 && grid[row_index][col_index + 1] == -1);
        }
        if (col_index > 0 && col_index < n)
        {
            at_v_junction |= (grid[row_index][col_index] == -1 && grid[row_index][col_index - 1] == 1);
        }
        return at_v_junction;
    }
    
    bool isAtWall(const int& col_index, const int& row_index, const std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        
        bool at_wall = false;
        if ( row_index < m && col_index == 0 && grid[row_index][col_index] == -1)
        {
            at_wall = true;
        }
        if (row_index < m && col_index == n - 1 && grid[row_index][col_index] == 1)
        {
            at_wall = true;
        }
        return at_wall;
    }
        
    int dropBallIntoCol(const int& starting_col, const std::vector<std::vector<int>>& grid)
    {
        int row_index, col_index;
        row_index = 0;
        col_index = starting_col;
        int m = grid.size();
        int n = grid[0].size();
        int result = -1;
        while (row_index < m && col_index < n && col_index >= 0 && !isAtVJunction(col_index, row_index, grid) && !isAtWall(col_index, row_index, grid))
        {
            switch (grid[row_index][col_index])
            {
                case 1:
                    col_index++;
                    break;
                case -1:
                    col_index--;
                    break;
                default:
                    result = -2;
                    return result;
            }
            row_index++;
        }
        if (row_index == m)
        {
            result = col_index;
        }
        return result;
    }
    
    vector<int> findBall(vector<vector<int>>& grid) {
        // maybe make this into a graph structure, where there is one root for each column
        // each node has an index m and index n, and a data value for left, right, and end value
        // for if can exit or blocked
        // and then traverse each root and set next according to its data value. 
        // do depth first search and return if get to end, or if blocked, and set that to 
        // roots end value.
        // to create the graph, in a worst case scenario where each route leads to end,
        // we have to visit each cell, so time O(n * m)
        // storage wise we would also have o(n * m)
        // to look up solution, would have O(1).
        
        // other idea is to loop over n, while loop till we clear the box, so till cur_row < m and cur_col < n
        // and we check value at m, n at each cell and then increment our m and n counters accordingly.
        // this would take O(1) storage
        // would take O(n * m) im time complexity.
        std::vector<int> solution;
        
        for (int ball_col = 0; ball_col < grid[0].size(); ball_col++)
        {
            int result = dropBallIntoCol(ball_col, grid);
            if (result == -2)
            {
                printf("error occured for ball starting in col %d", ball_col);
            }
            solution.push_back(result);
        }
        return solution;
    }
};
