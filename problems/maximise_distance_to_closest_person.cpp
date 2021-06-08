#include<algorithm>
using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        // approach 1
        // store an integer for seat position of max
        // store an integer for max length
        // loop over the seats, and for each seat, if someone is sitting there continue
        // else, loop over other seats to calculate distance
        // when looping over ith element, loop to  the end, then loop from start
        // looping from start to i is leftDistance, from i + 1 to end is rightDistance
        // before checking j, set flags for finding left or right person to false
        // when looping over other elements, check if the seat is full or empty.
        // if empty, calculate distance from current seat to that seat. if greater than the current l/r max, set the current l/r max
        // then if you find someone break from left or right loop, as we want closest person
        // before you break, set left/right person flag
        // after having checked closest seats, if left distance is less than or equal to right distance, OR we didn't find someone on right, we can check if left distance is greater than current max. If so, set. Do same check for right, if right distance less than left OR we didn't find someone on left, check if right distance is greater than max. If so, set.
        // 
        // two loops doing each half of array, from start to i and then from i to end
        // this will have O(N^2) in time complexity, and O(1) in space complexity
        
        int maxDistance = 0;
        int seatPos = 0;
        int leftDistance = 0;
        int rightDistance = 0;
        bool foundLeftPerson = false;
        bool foundRightPerson = false;
        
        for (int i = 0; i < seats.size(); i++) {
            // if someone sitting here, continue
            if (seats[i] == 1) {
                continue;
            }
            leftDistance = 0;
            rightDistance = 0;
            foundLeftPerson = false;
            foundRightPerson = false;
            for (int j = i - 1; j < i && j >= 0; j--) {
                // if someone sitting in j, calculate distance
                if (seats[j] == 1 && i - j > leftDistance) {
                    foundLeftPerson = true;
                    leftDistance = i - j;
                    break;
                }
            }
            
            for (int j = i + 1; j < seats.size(); j++) {
                if (seats[j] == 1 && j - i > rightDistance) {
                    foundRightPerson = true;
                    rightDistance = j - i;
                    break;
                }
            }
            
            // check closest distance
            if ((leftDistance <= rightDistance || !foundRightPerson) && leftDistance > maxDistance) {
                maxDistance = leftDistance;
                seatPos = i;
            }
            else if ((rightDistance < leftDistance || !foundLeftPerson) && rightDistance > maxDistance) {
                maxDistance = rightDistance;
                seatPos = i;
            }
        }
        return maxDistance;
        
    }
	
	// O(N) in time complexity
	// O(N) in space complexity
	int maxDistToClosest2(vector<int>& seats) {
		int N = seats.size();
		vector<int> left(N, N);
		vector<int> right(N, N);
		
		for (int i = 0; i < N; i++) {
			if (seats[i] == 1) {
				left[i] = 0;
			}
			else if (i > 0) {
				left[i] = left[i-1] + 1;
			}
		}
		
		for (int i = N - 1; i >= 0; i--) {
			if (seats[i] == 1) {
				right[i] = 0;
			}
			else if (i < N - 1) {
				right[i] = right[i+1] + 1;
			}
		}
		
		int maxDistance = 0;
		
		for (int i = 0; i < N; i++) {
			if (left[i] <= right[i] && left[i] > maxDistance) {
				maxDistance = left[i];
			}
			else if (right[i] < left[i] && right[i] > maxDistance) {
				maxDistance = right[i];
			}
		}
		return maxDistance;
	}
	
	
	int maxDistToClosestOpt(vector<in>& seats) {
		int N = seats.size();
		int prev = -1;
		int future = 0;
		int maxDistance = 0;
		
		for (int i = 0; i < N; i++) {
			if (seats[i] == 1) {
				prev = i;
			}
			else {
				while (future < N && seats[future] == 0 || future < i) {
					future++;
				}
			int left = prev == -1 ? N : i - prev;
			int right = future == N ? N : future - i;
			maxDistance = max(maxDistance, min(left, right));
			
			
			}
		}
		return maxDistance;
		
	}
};