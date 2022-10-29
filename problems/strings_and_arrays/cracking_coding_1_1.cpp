/*

Implmeent algo to determine if a string has all unique characters. what if cant use additional datastructures?

one approach, assume ascii and make a vector of len 26.
loop over str and for each char convert it to int and check that index in vector, if 0 add 1. else return false.
return true at end.

could also use a hash map which would be more space efficient as we dont allocate space we dont need. also still O(1) lookup.
time complexity o(n) if all unique, o(n) space complexity.

if no other datastructures, sort string first, then exit if previous same as next.
time complexity O(n logn) (for the sort), no space complexity.

feedback: missed ascii vs unicode. can check if str size greater than unique chars in alphabet. if more, cant be unique. easy optimization.
also, missed storage of merge sort. O(N). so second solution, not soo great.
*/

#include<cstdio>
#include <string>


void merge(std::string& str, int low, int middle, int high)
{
	std::string tmp = str;
	
	int helper_left = low;
	int helper_right = middle + 1;
	int current = low;
	
	while (helper_left <= middle && helper_right <= high)
	{
		int char1 = static_cast<int>(tmp[helper_left]);
		int char2 = static_cast<int>(tmp[helper_right]);
		
		if (char1 < char2)
		{
			str[current] = tmp[helper_left];
			helper_left++;
		}
		else
		{
			str[current] = tmp[helper_right];
			helper_right++;
		}
		current++;
	}	
	
	while (helper_left <= middle)
	{
		str[current] = tmp[helper_left];
		helper_left++;
		current ++;
	}
}

void sort(std::string& input_str, int low, int high)
{
	if (low < high)
	{
		int middle = (low + high) / 2;
		sort(input_str, low, middle);
		sort(input_str, middle + 1, high);
		merge(input_str, low, middle, high);
	}
}

bool hasUniqueChars(const std::string& input_str)
{
	if (input_str.size() <= 1)
	{
	  return true;
	}
	
	std::string sorted_str = input_str;
	sort(sorted_str, 0, sorted_str.size() - 1);
	for (int i = 1; i < sorted_str.size(); i++)
	{
		if (sorted_str[i] == sorted_str[i-1])
		{
			return false;
		}
	}
	return true;
	
}


int main()
{
	
	std::string my_str{"thisisjustatestandaquicklimitofourtimeonthisblueplanet"};
	bool res = hasUniqueChars(my_str);
	printf("%s\n%d\n", my_str.c_str(), res);
	
	my_str = "podnchtra";
	res = hasUniqueChars(my_str);
	printf("%s\n%d\n", my_str.c_str(), res);
	
	my_str = "";
	res = hasUniqueChars(my_str);
	printf("%s\n%d\n", my_str.c_str(), res);
}