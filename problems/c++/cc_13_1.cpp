/*

write a method to print last k lines of an input file using c++

we could read the file line by line into memory, counting total number of lines.

Then close and open and read once more line by line, counting how many lines we've read. stop at total lines - 1 - k. and then
print those ones. 

O(2N) time where N is the number of lines in file.
O(m) space, where m is line length

ofstream: Stream class to write on files
ifstream: Stream class to read from files
fstream: Stream class to both read and write from/to files.

can combine flags with bitwise |, ios::out | ios::app | ios::binary

feedback from optimal. reading twice is perhaps not ideal.
another way is to use a circular array, and keep track of last k strings. can keep track of start as well.
then only need to read it once.

*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void readKLines(std::string filename, int k)
{
	std::ifstream file;
	file.open(filename, std::ios::in);
	std::string line;
	int line_count = 0;
	
	while ( std::getline (file , line) )
	{
		line_count ++;
	}
	file.close();
	file.open(filename, std::ios::in);
  file.seekg (0, file.beg);

	for (int i = 0; i < line_count - k - 1; i++)
	{
		std::getline(file, line);
	}
	
	while (std::getline(file, line))
	{
		std::getline(file, line);
		std::cout << line << '\n';
	}
	
	file.close();
	
}

void readKLinesBetter(std::string filename, int k)
{
	std::cout << "new method" << std::endl;
	std::ifstream file;
	file.open(filename, std::ios::in);
	if (file)
	{
		file.seekg (0, file.end);
		int length = file.tellg();
    file.seekg (0, file.beg);
		
    char * buffer = new char [length];
		// read data as a block:
    file.read (buffer,length);
		
		file.close();
		
		int line_ctr = 0;
		int runner = length - 1;
		while (line_ctr < k && runner >= 0)
		{
		  if (buffer[runner] == '\n')
			{
				line_ctr++;
			}
			runner--;
		}
		
		runner++;
		
		while (runner < length)
		{
			runner++;
			std::cout << buffer[runner];
		}
		
		delete[] buffer;
	}
	std::cout << std::endl;
}

void readKLinesOptimal(std::string filename, int k)
{
	std::cout << "optimal method" << std::endl;
	std::ifstream file;
	file.open(filename, std::ios::in);
	std::vector<std::string> last_strs(k);
	int size = 0;
	while (file.good())
	{
		std::getline(file, last_strs[size % k]);
		size++;
	}
	
	// get start of circular array and size of it
	int start = size > k ? size % k : 0;
	int count = std::min(k, size);
	
	while (count > 0)
	{
		std::cout << last_strs[start] << std::endl;
		count--;
		start = start + 1 == k ? 0 : start + 1;
	}
	
}

int main()
{
	readKLines("ex_file.txt", 2);
	readKLinesBetter("ex_file.txt", 2);
	readKLinesOptimal("ex_file.txt", 2);
}