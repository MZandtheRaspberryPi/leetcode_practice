// implement a function void reverse(char* str) in c++ which reverses
// a null terminated string

#include<stdio.h>
#include <string.h>
#include <queue>

char ex_str[] = { 'a', 'b', 'c', 'd', '\0' };
char foo[3] = { 'e', 'f', '\0' };

// this is O(n^2) time complexitiy
// this is O(n) storage complexity
void reverse(char* str) {
	std::queue<char> str_q;
	for (int i = strlen(str) - 1; i >= 0; i--) {
		str_q.push(str[i]);
	}

	for (int i = 0; i < strlen(str); i++) {
		str[i] = str_q.front();
		str_q.pop();
	}
	
}

void reverse_optimal(char* str) {
	char* end = str;
	char tmp;
	if (str) {
		while (*end) { // find end of string
			++end;
		}
		--end; // set one char back, as null terminated string
		// swap chars @ start of string w/ end of string till pointers meet in middle
		while (str < end) {
			tmp = *str;
			*str++ = *end;
			*end-- = tmp;
		}
	}
}

int main() {
	reverse(ex_str);
	printf("%s\n", ex_str);
	reverse(foo);
	printf("%s\n", foo);
	reverse_optimal(ex_str);
	printf("%s\n", ex_str);
	reverse_optimal(foo);
	printf("%s\n", foo);
}