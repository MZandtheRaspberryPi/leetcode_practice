class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int tmp;
        for (int j = 0; j < k; j++) {
            tmp = nums[nums.size() - 1];
            for (int i = nums.size() - 1; i > 0; i--) {
                nums[i] = nums[i-1];                
            }
            nums[0] = tmp;
            
        } 
    }
};