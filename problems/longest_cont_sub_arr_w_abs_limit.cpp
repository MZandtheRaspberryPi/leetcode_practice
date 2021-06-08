#include<vector>
#include<cmath>
#include<deque>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        // loop through array
        // for each element in the array,
        // put it in a vector
        // look at other elements in array and check if that num minus that other element
        // is more than limit, if not, add to vector. if yes, break, check if greater than max size,
		// continue to next element
		
		// space complexity, O(N) in worst case where our whole vector fits limit
		// time complexity, O(N^2) in worst case where whole vector fits limit
        int maxSize = 1;
		
        for (int i = 0; i < nums.size(); i++) {
            vector<int> subNums(1, nums[i]);
			
			for (int j = i + 1; j < nums.size(); j++) {
				
				bool broken = false;
				for (int k = 0; k < subNums.size(); k++) {
					int diff = abs(subNums[k] - nums[j]);
					if (diff > limit) {
						broken = true;
						break;
					}
				}
				
				if (! broken) {
					subNums.push_back(nums[j]);
				}
				else {
					break;
				}
			}
			
			if (subNums.size() > maxSize) {
				maxSize = subNums.size();
			}
        }
		return maxSize; 
    }
	
	int longestSubarrayOptimal(vector<int>& A, int limit) {
		deque<int> maxd, mind;
		int i = 0, j;
		for (j = 0; j < A.size(); ++j) {
			while (!maxd.empty() && A[j] > maxd.back()) maxd.pop_back();
			while (!mind.empty() && A[j] < mind.back()) mind.pop_back();
			maxd.push_back(A[j]);
			mind.push_back(A[j]);
			if (maxd.front() - mind.front() > limit) {
				if (maxd.front() == A[i]) maxd.pop_front();
				if (mind.front() == A[i]) mind.pop_front();
				++i;
			}
		}
		return j - i;
	}
};