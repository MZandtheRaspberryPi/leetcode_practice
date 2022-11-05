/*
implement algo to perform basic string compression using count of repeated chars.
aabccccaaa would become a2b1c5a3. if compressed string wouldnt become smaller than original,
return original.


could make new empty string, push to it for each compress. but then when push to it, does it dynamically resize, doubling?

if so, make tmp char, set it to last char. set count to 1. start at second to last, loop to front. 
if current is same as prior, increment count by 1.
else, check if count greater than one. if so, convert the count into a string with atoi, and push it into vector. then push the last char into vector. then set count to 1.

set char to current, continue.

at end convert vector of strings to string. strings mutable in c++ tho, so not a huge concern.

operate in O(N) time complexity, O(N) storage.

feedback: could have checked count of compressed string before calculating, then return if not. didnt read prompt,
badd should be b1a1d2, not bad2. 

c++ str concatenation, strings mutable. but owuld have to resize first. so code would have n^2 time complexity if didnt.
or use osstream:
#include <sstream>

std::ostringstream oss;
    for (auto &word : words) {
        oss << word;
    }
    return oss.str();

*/

#include <stdio.h>
#include <string>
#include <vector>


std::string compressString(std::string input_str)
{
	// empty, single letter a, or double letter aa (a1 compressed, same length)
	if (input_str.size() < 3)
	{
		return input_str;
	}
	
	char tmp = input_str[input_str.size() - 1];
	int count = 1;
	std::vector<std::string> compressed_str_vect;
	
	for (int i = input_str.size() - 2; i >= 0; i--)
	{
		if (input_str[i] == tmp)
		{
			count++;
		}
		else if (count > 1)
		{
			std::string string_to_add(1, tmp);
			compressed_str_vect.push_back(std::to_string(count));
			compressed_str_vect.push_back(string_to_add);
			count = 1;
		}
		else
		{
			std::string string_to_add(1, input_str[i]);
			compressed_str_vect.push_back(string_to_add);
			
		}
		
		tmp = input_str[i];
	}
	
	// check if first one was repeated
	if (count > 1)
	{
		std::string string_to_add(1, tmp);
		compressed_str_vect.push_back(std::to_string(count));
		compressed_str_vect.push_back(string_to_add);
		count = 1;
	}
	
	
	std::string output_str;
	for (int i = compressed_str_vect.size() - 1; i >= 0 ; i--)
	{
		output_str += compressed_str_vect[i];
	}
	
	if (output_str.size() < input_str.size())
	{
		return output_str;
	}
	else
	{
		return input_str;
	}
	
	
	
}


int main()
{
	std::string input_str{"aabbccccdddddeetasfdl;knasdgggg;liasdfnasdfl;knasdfkkk"};
	std::string compressed_str = compressString(input_str);
	printf("%s\n%s\n\n", input_str.c_str(), compressed_str.c_str());
}