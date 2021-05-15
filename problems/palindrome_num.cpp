class Solution{
public:
	bool isPalindrome(int x) {
		// if negative number, not palindrome
		// if ends in zero, has to start with 0
		// only number like that is 0, so if not 0 its not palindrome
		if (x < 0 || (x % 10 == 0 && x != 0)) {
			return false;
		}
		
		// let's check if half number reversed is equal to half number
		// as this way we don't need to convert to string with non-constant memory
		// and additionally half the number will let us avoid overflow errors
		int reversedX = 0;
		while (reversedX < x) {
			reversedX = reversedX * 10 + x % 10;
			x /= 10;
		}
		// if even number, they'll be equal
		// if odd, like 10301, we'll have 10 and 103, so ignore middle digit
		if ( reversedX == x || reversedX / 10 == x) {
			return true;
		}
		else {
			return false;
		}
	}
}