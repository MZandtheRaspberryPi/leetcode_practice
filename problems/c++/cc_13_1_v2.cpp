// we will loop through file line by line counting size, and writing to a circular array of size k
// the index we write in array will be size % k

// when we are through the file, we will loop over array and print it, while count is greater than 0
// the starting index of the loop will be 0 if the size is less than k
// else the starting index will be size - k % k

// so if we have 5 lines, and k is 2
// we will start on index 3 % 2 1.

// we set count to min of k or size. 

// time, O(N) where N is num of lines in file
// space, O(k)

// clarify, do we start counting from last line in file, or how does that work?

// while count > 0, print line. set next line to start_index + 1 if not == k else 0.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void printKthLinesFile(const std::string& file_path, const int k)
{
	std::ifstream file;
	file.open(file_path, std::ios::in);
	std::vector<std::string> kth_lines(k);
	int size = 0;
	while (file.good())
	{
		std::getline(file, kth_lines[size % k]);
		size++;
	}
	
	int start_index = size < k ? 0 : (size - k) % k;
	int count = std::min(k, size);
	
	std::cout << "size: " << size << " start: " << start_index << " count: " << count << std::endl;
	
	while (count > 0)
	{
		std::cout << kth_lines[start_index] << std::endl;
		count--;
		start_index = start_index + 1 == k ? 0 : start_index + 1;
	}

}


int main()
{
	printKthLinesFile("ex_file.txt", 5);
}