/*
Write a method to replace all spaces in a string wtih %20. Assume enough room in string, and assume
given true length of string (if java, use char array so can do in place
*/

// is the char array null terminated?

#include<stdio.h>
#include<string.h>

char chr_arr[18] = { 'M', 'r', ' ', 'J', 'o', 'h', 'n', ' ', 'S', 'm', 'i', 't', 'h', ' ', ' ', ' ', ' ', '\0' };
char chr_arr2[21] = {' ', 'M', 'r', ' ', 'J', 'o', 'h', 'n', ' ', 'S', 'm', 'i', 't', 'h', ' ', ' ', ' ', ' ', ' ', ' ', '\0' };

// find length of char array
// go over array in reverse, put first char at new end and keep going back from there
// replacing spaces till at start

// time complexity here is n, as loop over once to find end, loop over a second time to set values
// space complexity is O(1), constant, as we store a couple characters and a bool
void replace_spaces(char* str) {
	char* end = str;
	char tmp;
	bool repl_end = false;
	if (str) {
		// finding end of char array
		while (*end) {
			++end;
		}
		// set back one from null terminated string
		--end;

		// printf("end: %c\n", *end);
		
		for (char* place = end; str <= place; --place) {
			// printf("place: %c\n", *place);
			tmp = *place;
			// printf("tmp: %c\n", tmp);
			if (tmp == ' ' && !repl_end) {
				continue;
			}
			else if (tmp != ' ' && !repl_end) {
				*end = tmp;
				repl_end = true;
				end--;
			}
			else if (tmp != ' ' && repl_end) {
				*end = tmp;
				end--;
			}
			else if (tmp == ' ' && repl_end) {
				// moving back 3 in the actual string to put in %20
				*end = '0';
				end--;
				*end = '2';
				end--;
				*end = '%';
				end--;
			}
			
		}
	}
}


// this O(n) time complexity, O(1) space complexity
void replaceSpacesOptimal(char str[], int length) {
	int spaceCount = 0;
	int newLength = 0;
	int i = 0;
	for (i = 0; i < length; i++) {
		if (str[i] == ' ') {
			spaceCount++;
		}
	}

	newLength = length + spaceCount * 2;
	str[newLength] = '\0';

	for (i = length - 1; i >= 0; i--) {
		if (str[i] == ' ') {
			str[newLength - 1] = '0';
			str[newLength - 2] = '2';
			str[newLength - 3] = '%';
			newLength = newLength - 3;
		}
		else {
			str[newLength - 1] = str[i];
			newLength = newLength - 1;
		}
	}	
}

int main() {
	printf("%s\n", chr_arr);
	replaceSpacesOptimal(chr_arr, 13);
	printf("%s\n", chr_arr);
	printf("%s\n", chr_arr2);
	replace_spaces(chr_arr2);
	printf("%s\n", chr_arr2);
}