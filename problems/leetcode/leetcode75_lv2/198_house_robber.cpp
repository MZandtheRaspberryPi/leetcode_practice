#include <algorithm>

int robSearch(const vector<int>& nums, int i, vector<int>& cache)
{
    if (i < 0)
    {
        return 0;
    }
    if (cache[i] > -1)
    {
        return cache[i];
    }
    int res = std::max(robSearch(nums, i - 2, cache) + nums[i], robSearch(nums, i - 1, cache));
    cache[i] = res;
    return res;
}

class Solution {
public:
    int robMySol(vector<int>& nums) {
       // for recursion/DP, bottom up or top down
       // if we start at the last item, whether we rob the house is determined by
       // if the current house plus the house 2 back, is greater than the house 1 back.
       // so we could do top down recursion

       // now, we could cache the result of the decision at each step, and check for that.

       // time, O(N)
       // space, O(N + logn) logn for recursive calls
       std::vector<int> cache(nums.size(), -1);
       return robSearch(nums, nums.size() - 1, cache);
    }

    int robOptimal(vector<int>& nums) {
       // for recursion/DP, bottom up or top down
       // if we do bottom up, we populate our cache for the first two entries
       // we can then do iteration instead of recursion

       // time, O(N)
       // space, O(N)
        std::vector<int> cache(nums.size() + 1, 0);
        cache[0] = 0;
        cache[1] = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            int val = nums[i];
            cache[i] = max(cache[i], cache[i - 1] + val);
        }

        return cache[nums.size()];
    }

    int rob(vector<int>& nums) {
        // for recursion/DP, bottom up or top down
        // if we do bottom up, we populate our cache for the first two entries
        // we can then do iteration instead of recursion
        // and then we keep those values in two vars

        // time, O(N)
        // space, O(1)
        if (nums.size() == 0) return 0;
        int prev1 = 0;
        int prev2 = 0;

        for (const int& num : nums)
        {
            int tmp = prev1;
            prev1 = max(prev2 + num, prev1);
            prev2 = tmp;
        }
        return prev1;
    }
};
