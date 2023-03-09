void DFS(const vector<vector<int>>& heights, vector<vector<bool>>& visited, const int& i, const int& j)
{

    int num_rows = heights.size();
    int num_cols = heights[0].size();

    visited[i][j] = true;

    // we want to visit every tile north, south, east, west,
    // if it has height greater than or equal to our height
    // if it is not out of bounds
    // and if it has not been visited
    const int cur_height = heights[i][j];

    if (i - 1 >= 0 && heights[i - 1][j] >= cur_height && !visited[i - 1][j])
    {
        int new_row = i - 1;
        DFS(heights, visited, new_row, j);
    }
    if (i + 1 < num_rows && heights[i + 1][j] >= cur_height && !visited[i + 1][j])
    {
        int new_row = i + 1;
        DFS(heights, visited, new_row, j);
    }

    if (j - 1 >= 0 && heights[i][j - 1] >= cur_height && !visited[i][j - 1])
    {
        int new_col = j - 1;
        DFS(heights, visited, i, new_col);
    }

    if (j + 1 < num_cols && heights[i][j + 1] >= cur_height && !visited[i][j + 1])
    {
        int new_col = j + 1;
        DFS(heights, visited, i, new_col);
    }
}


class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // we could use storage, m*n storage, to store whether a cell leads to the pacific.
        // same to say whether leads to atlantic
        // then we go through all the sides of the matrix, and dfs through them.
        // start with end, mark as true if leads there... 
        int num_rows = heights.size();
        if (num_rows == 0)
        {
            return vector<vector<int>>(0);
        }
        int num_cols = heights[0].size();
        if (num_cols == 0)
        {
            return vector<vector<int>>(0);
        }

        vector<vector<bool>> pacific(num_rows, vector<bool>(num_cols, false));
        vector<vector<bool>> atlantic(num_rows, vector<bool>(num_cols, false));

        for (int i = 0; i < num_rows; i++)
        {
            DFS(heights, pacific, i, 0);
            DFS(heights, atlantic, i, num_cols - 1);
        }

        for (int j = 0; j < num_cols; j++)
        {
            DFS(heights, pacific, 0, j);
            DFS(heights, atlantic, num_rows - 1, j);
        }

        vector<vector<int>> result;
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                if (pacific[i][j] && atlantic[i][j])
                {
                    vector<int> coord = {i, j};
                    result.push_back(coord);
                }
            }
        }
        return result;

    }
};
