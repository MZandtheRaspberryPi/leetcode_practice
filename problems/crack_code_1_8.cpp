// assume have method isSubstring, checks if one word is substring of another.
// given two strings, s1 and s2, write code to check is s2 is a rotation of s1 using only one call to substring.
// eg, "waterbottle" is a rotation of "erbottlewat".

#include<stdio.h>
#include<string>

int calcArrLength(const char* s1) {
	if (s1) {
		int lenS1 = 1;
		while (*s1) {
			lenS1++;
			s1++;
		}
		// setting back from null ptr
		lenS1--;
		// setting back to start
		s1 = s1 - lenS1;
		return lenS1;
	}
	else {
		return 0;
	}
}

bool isSubstring(const char* s1, const char* s2) {
	// checks if s2 is a substring of s1

	if (s1 && s2) {
		// get lengths
		int lenS1 = calcArrLength(s1);
		int lenS2 = calcArrLength(s2);

		// checking substring
		if (lenS1 < lenS2) {
			return false;
		}

		int successiveLetterCount = 0;
		for (int i = 0; i < lenS1; i++) {
			// check if letter in s1 matches s2 val
			if (s1[i] == *s2) {
				successiveLetterCount++;
				s2++;
			}
			// else if we had prior matches before this letter, reset
			else if (successiveLetterCount > 0) {
				s2 -= successiveLetterCount;
				successiveLetterCount = 0;
				// and check if new starting point would be good for first letter in s2
				if (s1[i] == *s2) {
					successiveLetterCount++;
					s2++;
				}
			}

			// if we got all the matches, exit from loop
			if (successiveLetterCount == lenS2) {
				break;
			}
		}

		if (successiveLetterCount != lenS2) {
			return false;
		}
		else {
			return true;
		}

	}
	else {
		return false;
	}
}



bool checkRotation(std::string s1, std::string s2) {
	// checks if s2 is a rotation of s1
	// eg, "waterbottle" is a rotation of "erbottlewat"
	// with one call to subString

	// we know that we need to split s1 into x and y such that xy=s1 and yx = s2. wherever division is, yx will 
	// always be a substring of xyxy. That is, s2 will always be substring of s1, s1.

	int lenS1 = s1.length();

	if (lenS1 == s2.length() && lenS1 > 0) {
		std::string s1s1 = s1 + s1;
		return isSubstring(s1s1.c_str(), s2.c_str());


	}
	else {
		return false;
	}

}


int main() {
	char s1[] = {'a', 'b', 'b', 'c', 'd', 'e', '\0'};
	char s2[] = { 'b', 'c', '\0'};
	printf("%s\n", isSubstring(s1, s2) ? "true" : "false");

	char s3[] = { 'b', 'a', 'd', ' ', 'a', 'p', 'p', 'l', 'e', 's', '\0' };
	char s4[] = {'a', 'p', 'p', 'l', 'e', 's', '\0' };
	printf("%s\n", isSubstring(s3, s4) ? "true" : "false");

	char s5[] = { 'w', 'a', 't', 'e', 'r', 'b', 'o', 't', 't', 'l', 'e', '\0' };
	char s6[] = { 'e', 'r', 'b', 'o', 't', 't', 'l', 'e', 'w', 'a', 't', '\0' };

	std::string str1 = "waterbottle";
	std::string str2 = "erbottlewat";
	printf("%s\n", checkRotation(str1, str2) ? "true" : "false");

	std::string str3 = "nitwit";
	std::string str4 = "witnik";
	printf("%s\n", checkRotation(str3, str4) ? "true" : "false");
}