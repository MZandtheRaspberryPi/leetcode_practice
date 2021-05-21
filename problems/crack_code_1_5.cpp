// implement simple compression using counts of repeated characters aaabcccaaa -> a3b1c3a3
// if string wouldn't become smaller, return original string

// is this going to come in null terminated array?
// could we get blank strings?
// constraints on length of string, could the number of repeated letters go above an int max? or above 10?

// algorithm design
// will need dynamically sized vector as we don't know true size str at start

// will also need to get count of str length first

// could loop through str once, seeing how many letters change from one char to another. we keep track of this in a vector dynamically sized array
// that then stores counts after. 

// we then check length of the given char array in comparison to the vector we will have and if needed convert the given char array to a vector and return that
// if compression is successful this will be O(n^2) in time complexity and O(n - repeated letters) in storage complexity
// will have to watch out for longer than 10 repeats and so on, and be flexible with that regard

// string buffer is the way to go here as it will take less timae complexity

#include<stdio.h>
#include<vector>

char arr[] = { 'a', 'a', 'a', 'b', 'b', 'a', 'a', 'a', 'a', '\0' };

char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

std::vector<char> compress(char str[]) {
	std::vector<char> compressed;
	if (str) {
		int length = 1;
		// start conditions at start of string, so first letter is counted once and we see it
		char tmp = str[0];
		int repeat_count = 0;

		while (*str) {
			length++;
			++str;
		}
		printf("length: %d\n", length);
		length--;
		// moving str back to start
		str = str - length;


		for (int i = 0; i <= length; i++) {
			if (tmp == str[i]) {
				repeat_count++;

			}
			else {
				compressed.push_back(tmp);
				compressed.push_back(digits[repeat_count]);
				tmp = str[i];
				repeat_count = 1;
			}

		}

		if (compressed.size() < length) {
			return compressed;
		}
		else {
			std::vector<char> old_vect(str, str + length);
			return old_vect;
		}
	}
	else {
		return compressed;
	}

};


int main() {
	
	std::vector<char> comp = compress(arr);
	for (int i = 0; i < comp.size(); i++) {
		printf("%c%", comp[i]);
	}
	
}