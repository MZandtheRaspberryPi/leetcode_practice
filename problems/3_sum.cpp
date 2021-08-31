#include<algorithm>
#include<map>

/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.
 */

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // could loop through every possible combo of three characters and add them, n^3
        vector<vector<int>> triplets = vector<vector<int>>();
        if (nums.size() < 3) {
            return triplets;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (j == i) {
                    continue;
                }
                for (int k = 0; k < nums.size(); k++) {
                    if (k == j || k == i) {
                        continue;
                    }
                    
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> vect_to_add = vector<int>();
                        vect_to_add.push_back(nums[i]);
                        vect_to_add.push_back(nums[j]);
                        vect_to_add.push_back(nums[k]);
                        sort(vect_to_add.begin(), vect_to_add.end());
                        triplets.push_back(vect_to_add);
                    }
                    
                }
            }
        }
        
        map<vector<int>, int> m;
        vector<vector<int>> fin_triplets = vector<vector<int>>();
        
        for (int i = 0; i < triplets.size(); i++) {
            if (m.find(triplets[i]) != m.end()) {
                m[triplets[i]] += 1;
            }
            else {
                m[triplets[i]] = 1;
            }
        }
        
        for (map<vector<int>,int>::iterator it = m.begin(); it != m.end(); it++) {
            fin_triplets.push_back(it->first);
        }
        return fin_triplets;
        
    }
	
	vector<vector<int>> threeSumOpt(vector<int>& nums) {
		vector<vector<int> > res;

		std::sort(num.begin(), num.end());

		for (int i = 0; i < num.size(); i++) {
			
			int target = -num[i];
			int front = i + 1;
			int back = num.size() - 1;

			while (front < back) {

				int sum = num[front] + num[back];
				
				// Finding answer which start from number num[i]
				if (sum < target)
					front++;

				else if (sum > target)
					back--;

				else {
					vector<int> triplet = {num[i], num[front], num[back]};
					res.push_back(triplet);
					
					// Processing duplicates of Number 2
					// Rolling the front pointer to the next different number forwards
					while (front < back && num[front] == triplet[1]) front++;

					// Processing duplicates of Number 3
					// Rolling the back pointer to the next different number backwards
					while (front < back && num[back] == triplet[2]) back--;
				}
				
			}

			// Processing duplicates of Number 1
			while (i + 1 < num.size() && num[i + 1] == num[i]) 
				i++;

		}
		
		return res;
	
	}
};