#include<limits.h>
#include<stdio.h>

class Solution {
public:
	int reverse(int x) {
		int rev = 0;
		int remainder;
		while (x != 0) {
			remainder = x % 10;
			x /= 10;
			// if we will overload return 0
			// INT_MAX % 10 will give last digit of int max
			if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && remainder > INT_MAX % 10)) {
				return 0;
			}
			else if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && remainder < INT_MIN % 10)) {
				return 0;
			}
			rev = rev * 10 + remainder;

		}
		return rev;
	}
};

int main() {
	Solution sol = Solution{};
	int result = sol.reverse(-123);
	printf("Result %d", result);
}