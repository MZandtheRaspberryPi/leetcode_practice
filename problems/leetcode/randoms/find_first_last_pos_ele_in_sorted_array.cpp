int search(const vector<int>& nums, const int& low, const int& high, const int& search_value)
{
    if (low > high || nums.size() == 0)
    {
        return -1;
    }
    int mid = (low + high) / 2;
    int new_low, new_high;
    if (nums[mid] == search_value)
    {
        return mid;
    }
    else if (nums[mid] < search_value)
    {
        new_low = mid + 1;
        new_high = high;
    }
    else
    {
        new_low = low;
        new_high = mid - 1;
    }
    return search(nums, new_low, new_high, search_value);
    
}

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // binary search to find value
        // then search left and right till out of value
        
        // find value
        // set start_index to mid and end_index to mid
        // while nums[start_index] == search_value and start_index >= 0, move it left
        // same for right index
        // then make new vector and push_back from start index to and including end index
        // time complexity O(logn), if the whole array is solution, then O(N) as we expand indices
        // after binary search. storage complexity O(m) where m is number of solutions in array
        int value_index = search(nums, 0, nums.size() - 1, target);
        if (value_index == -1)
        {
            return std::vector<int>(2, -1);
        }
        int start_index, end_index;
        start_index = end_index = value_index;
        while(start_index > 0 && nums[start_index - 1] == target)
        {
            start_index--;
        }
        
        while(end_index < nums.size() - 1 && nums[end_index + 1] == target )
        {
            end_index++;
        }
        std::vector<int> result(2);
        result[0] = start_index;
        result[1] = end_index;
        return result;
    }
};
