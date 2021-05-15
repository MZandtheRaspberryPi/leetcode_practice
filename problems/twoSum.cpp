#include<vector>
#include<iostream>
#include<unordered_map>
#include<exception>

class Solution {
public:
	// find the index of two numbers in array that will sum to target
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target && i != j) {
                    return std::vector<int> {i, j};
                }
            }
        }
        throw std::runtime_error{ "No solution found for given array and target!" };
    }
    // this does 2 passes over array, but uses hash table to store index so is O(n) in runtime and o(n) in storage
    std::vector<int> twoSumHash2Pass(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> index_value_map;
        for (int i = 0; i < nums.size(); i++) {
            index_value_map[nums[i]] = i;
        }
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (index_value_map.find(complement) == index_value_map.end()) {
                continue;
            }
            else if (index_value_map[complement] != i){
                return std::vector<int> {i, index_value_map[complement]};
            }
        }
        
        throw std::runtime_error{ "No solution found for given array and target!" };
    }

    // this does 1 pass over array and uses hash table to store index so is O(n) in runtime and o(n) in storage
    std::vector<int> twoSumHash1Pass(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> index_value_map;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            // if we already have this number stored, check if its the complement, if so we solved
            // if not update hash and continue
            if (index_value_map.find(complement) != index_value_map.end() && 
                nums[i] == complement) {
                return std::vector<int> {index_value_map[complement], i};
            }
            else {
                index_value_map[nums[i]] = i;
            }
            
            if (index_value_map.find(complement) == index_value_map.end()) {
                continue;
            }
            else if (index_value_map[complement] != i) {
                return std::vector<int> {index_value_map[complement], i};
            }
        }
        throw std::runtime_error{ "No solution found for given array and target!" };
    }
};

int main() {
    Solution sol{};
    std::vector<int> test_arr = { 2, 7, 11, 15 };
    int target = 9;
    std::vector<int> result = sol.twoSum(test_arr, target);
    std::cout << result.at(0) << ' ';
    std::cout << result.at(1) << ' ';
    std::cout << '\n';

    test_arr = { 3, 2, 4};
    target = 6;
    result = sol.twoSum(test_arr, target);
    std::cout << result.at(0) << ' ';
    std::cout << result.at(1) << ' ';
    std::cout << '\n';

    test_arr = { 3, 3 };
    target = 6;
    result = sol.twoSum(test_arr, target);
    std::cout << result.at(0) << ' ';
    std::cout << result.at(1) << ' ';
}