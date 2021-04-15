class Solution:
    def twoSum_brute_force(self, nums: list[int], target: int) -> list[int]:
        # for each entry in the array, check all the other entries
        # to see if you can sum to the target
        for i in range(len(nums)):
            for j in range(len(nums)):
                if i == j:
                    continue
                if nums[i] + nums[j] == target:
                    return [i, j]

    def twoSum_two_pass_hash(self, nums: list[int], target: int) -> list[int]:
        """time complexity: O(N), storage complexity O(N)"""
        # for each entry in the array, check all the other entries
        # to see if you can sum to the target
        hash_table = {}
        for i in range(len(nums)):
            hash_table[nums[i]] = i
        for i in range(len(nums)):
            complement = target - nums[i]
            if complement in hash_table.keys() and not hash_table[complement] == i:
                return [i, hash_table[complement]]
        raise Exception("No solution found for given array and target sum")


    def twoSum_one_pass_hash(self, nums: list[int], target: int) -> list[int]:
        """time complexity: O(N), storage complexity O(N)"""
        # for each entry in the array, check all the other entries
        # to see if you can sum to the target
        hash_table = {}
        for i in range(len(nums)):
            complement = target - nums[i]
            if not nums[i] in hash_table.keys():
                hash_table[nums[i]] = i
            else:
                # if already added number to hash table, and it is the complement
                if complement in hash_table.keys():
                    return [hash_table[complement], i]
            # if complement is in array and also we can't use same number twice
            if complement in hash_table.keys() and not hash_table[complement] == i:
                return [hash_table[complement], i]
        raise Exception("No solution found for given array and target sum")


if __name__ == "__main__":
    solution = Solution()
    test_results = solution.twoSum_brute_force([2, 7, 11, 15], 9)
    print(test_results)
    test_results = solution.twoSum_two_pass_hash([2, 7, 11, 15], 9)
    print(test_results)
    test_results = solution.twoSum_one_pass_hash([2, 7, 11, 15], 9)
    print(test_results)