class Solution {
public:
    int search(vector<int>& nums, int target) {
        // binary search with rotation
        // we will check the middle and the left. if the left is less than the middle,
        // we know the left side is normal. we can use that ot check if we should search the left or right.
        // if the left is greater than middle, we can use the right to check which side we should search.
        int low = 0;
        int high = nums.size() - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (nums[mid] == target) return mid;
            // left is increasing to mid, its normal
            if (nums[mid] > nums[low])
            {
                if (target >= nums[low] && target < nums[mid])
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }
            else if (nums[mid] < nums[low])// use the right to determine which side to search
            {
                if (target <= nums[high] && target > nums[mid])
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
            else
            {
                // if middle equals left, then we are not sure which side to use. we can check right, else we will have to use both sides.
                if (nums[low] != target)
                {
                    low++;
                }
                else
                {
                    return true;
                }
            }
        }
        return -1;
    }
};
