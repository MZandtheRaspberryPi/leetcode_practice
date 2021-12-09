class Solution {
public:
    // create vector to keep track of visited nodes
    // create province count init to 0
    // loop from i = 0 to i < isConnected.size()
    // for each city, add one to province count, and search the list of its connected
    // in seach, set visited for that city to true
    // then loop through the list of its connected, and search each city.
    // when is visited is true, return 0, else search that node
    // loop from j + 0 to j < isConnected.size(), if i == j continue
    // depth first search
    
    // time complexity. If all cities connected, it will be O(N), as we will loop through each city once. If all cities are not connected, we will still loop through each city once.
    // storage complexity is O(N), as we are storing a vector of bools, and a constant
    void search(int cityIndex, const vector<vector<int>>& isConnected, vector<bool>& isVisited)
    {
        if (isVisited[cityIndex])
        {
            return;
        }
        else
        {
            isVisited[cityIndex] = true;
            for (int j = 0; j < isConnected.size(); j++)
            {
                if (j == cityIndex)
                {
                    continue;
                }
                else if (isConnected[cityIndex][j] == 1)
                {
                    search(j, isConnected, isVisited);
                }
            }
        }
    }
    
    
    int findCircleNum(vector<vector<int>>& isConnected) {
        vector<bool> isVisited(isConnected.size(), false);
        int provinceCount = 0;
        for (int i = 0; i < isConnected.size(); i++)
        {
            if (isVisited[i])
            {
                continue;
            }
            else
            {
                provinceCount++;
                search(i, isConnected, isVisited);
            }
        }
        return provinceCount;
    }
};
