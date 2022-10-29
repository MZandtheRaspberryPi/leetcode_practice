/* given two strings write a method to determine if one is permutation of another

the letters counts have to be equal.

So, if we are ascii, could make a vector for ASCII characters and loop over string1 and count.
Then, loop over string2 and subtract, if go negative return false. else if at the end we have positive left, return false.
time complexity O(N), space O(1), but some space for ascii even if constant.

could use a hash table, less up front storage.

could also sort both strings then go through and compare 1 by 1. time complexity O(nlogn) space, depends on sort method, O(n) if merge sort

we will go hash table route.
*/

#include <map>
#include <string>

bool is_char_in_map(const std::map<char, int>& letter_count, char char_to_find)
{

		return letter_count.find(char_to_find) != letter_count.end();
}

bool isPermutation(std::string str1, std::string str2)
{
	if (str1.size() != str2.size())
	{
		return false;
	}
	
	
	std::map<char, int> letter_count;
	
	for (int i = 0; i < str1.size(); i++)
	{
		if (is_char_in_map(letter_count, str1[i]))
		{
			letter_count[str1[i]]++;
		}
		else
		{
			letter_count[str1[i]] = 1;
		}
		
		if (is_char_in_map(letter_count, str2[i]))
		{
			letter_count[str2[i]]--;
		}
		else
		{
			letter_count[str2[i]] = -1;
		}
	
	}
	
	std::map<char, int>::iterator it;
	for (it = letter_count.begin(); it != letter_count.end(); it++)
	{
		if (it->second != 0)
		{
			return false;
		}
	}
	return true;
	
}


int main()
{
	std::string str1 = "aabbccdd";
	std::string str2 = "ddccbbaa";
	
	printf("%s and %s: %d\n", str1.c_str(), str2.c_str(), isPermutation(str1, str2));
	
	str1 = "asfdjk;";
	str2 = "qwerjkl";
	printf("%s and %s: %d\n", str1.c_str(), str2.c_str(), isPermutation(str1, str2));
	
}