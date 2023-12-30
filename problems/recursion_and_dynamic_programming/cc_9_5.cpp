/*
write a method to compute all permutations of a string

well each character can go in any spot, and other characters in any other spot.

base case and solve
if we have "a"
only "a"

if we have "ab"
"ab" "ba"

"abc"
"cab" "acb"  "abc"  "cba" "bca" "bac"

we put c into each spot in the prior string.

so if we have n-1 solution, we add our new letter to each position in it.

so, function takes ref to old array, ref to new array, index of char
it gets n-1 chars
if n == 0, return first letter
else
go over array, for each entry add our string to each entry in every position and put into array at back.
*/

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

void get_all_substrs(const std::string& my_str, std::vector<std::string>& all_substrs, uint64_t index)
{
	if (index == 0)
	{
		std::string my_substr = my_str.substr(index, 1);
		all_substrs.push_back(my_substr);
		return;
	}
	
	get_all_substrs(my_str, all_substrs, index - 1);
	const uint64_t num_substrs = all_substrs.size();
	const std::string my_substr = my_str.substr(index, 1);
	for (uint64_t i = 0; i < num_substrs; i++)
	{
		std::string substr = all_substrs[i];
		for (uint64_t j = 0; j < substr.size(); j++)
		{
			std::string new_substr = substr;
			new_substr.insert(j, my_substr);
			all_substrs.push_back(new_substr);
		}
		substr.insert(substr.size(), my_substr);
		all_substrs.push_back(substr);
	}
	
}

std::vector<std::string> get_all_substrs(const std::string& my_str)
{
	std::vector<std::string> all_substrs;
	get_all_substrs(my_str, all_substrs, my_str.size() - 1);
	return all_substrs;
	
}

int main()
{
	std::string my_str = "abc";
	std::vector<std::string> all_substrs = get_all_substrs(my_str);
	for (const auto& val : all_substrs)
	{
		std::cout << val << ", ";
	}
}