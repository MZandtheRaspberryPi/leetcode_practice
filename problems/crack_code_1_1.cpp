// implement an algo to determine if a string has all unique characters. what if you can't use add'tl data structures?

// so, could create an array of all possible characters. if ASCII, 256 characters. 
// then loop through string and convert character to int for which ascii character, add to that in array.
// then loop through array and check if any greater than 1.
// time complexity O(N), space complexity O(1)

// if want to store data, hash table is an option.

#include<stdio.h>

bool isUnique(char* arr) {
	int ascii[256] = { 0 };
	int asciiIndex;
	while (*arr != '\0') {
		asciiIndex = (int)*arr;
		ascii[asciiIndex] += 1;
		arr++;
	}

	for (int i = 0; i < 256; i++) {
		if (ascii[i] > 1) return false;
	}
	return true;
}

int main() {
	
	char arr[] = { 'a', 'b', 'c', 'd', 'a', 'e', 'f', '\0' };
	bool res = isUnique(arr);
	printf("%d\n", res);

}