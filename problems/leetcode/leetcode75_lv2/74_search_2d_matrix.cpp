class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // treat as big array
        // low = 0, high = m * n - 1
        // then to translate to indices
        // m = num rows
        // n = num cols
        // matrix[x][y] = matrix[mid / m][mid % n]

        // time complexity: O(log(m * n))
        // storage: O(1)
        int num_rows = matrix.size();
        int num_cols = matrix[0].size();

        int low = 0;
        int high = num_rows * num_cols - 1;

        while (low <= high)
        {
            int mid = (low + high) / 2;
            int mid_val = matrix[mid / num_cols][mid % num_cols];
            if (mid_val == target)
            {
                return true;
            }
            else if (mid_val < target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return false;
    }
};
