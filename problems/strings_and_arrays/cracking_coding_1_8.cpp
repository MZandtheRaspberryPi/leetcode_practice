/*

assume have method is sub string which returns if one string is substr of another.
given 2 strings, s1, s2, write code to check if s2 is a rotation of s1, using only
1 call to isSubStr, eg watterbottle is rotation of erbottlewat.

loop through s2, looking for first letter of s1. make sure that each other letter after is the next index in s1.
then check that the string from the 0th index to but not including location of first letter of s1, is a substr of s1.

This would have O(N) time complexity in a worst case, where first letter is in 0th index, not including substr method.
this would have constant space complexity. not including substr method.

feedback. could have been more clever and realized that the substring has to be in str1 + str 1. so could have just made new string buffer
and checked that

*/

#include <string>

bool isSubStr(std::string str, std::string sub_str)
{
	bool sub_str_found = false;
	int sub_str_index = 0;
	for (int i = 0; i < str.size(); i++)
	{
		for (int j = 0; j < sub_str.size(); j++)
		{
			if (i + j > str.size() - 1 || !(str[i + j] == sub_str[sub_str_index]))
			{
				break;
			}
			
			if (sub_str_index == sub_str.size() - 1)
			{
				sub_str_found = true;
			}
			sub_str_index++;
		}
		
		if (sub_str_found)
		{
			break;
		}
	}
	
	return sub_str_found;
	
}

bool isRotation(std::string str1, std::string str2)
{
	
	if (!(str2.size() == str1.size()))
	{
		return false;
	}
	
	int first_letter_index = -1;
	bool found_rotation_point = false;
	for (int i = 0; i < str2.size(); i++)
	{
		if (str2[i] == str1[0])
		{
			
		  for (int j = i + 1; j < str2.size(); j++)
			{
				if (!(str1[0 + j - i] == str2[j]))
				{
					break;
				}
				
				if (j == str2.size() - 1)
				{
					found_rotation_point = true;
				}
			}
			
			if (found_rotation_point)
			{
				first_letter_index = i;
				break;
			}
		}
	}
	
	if (first_letter_index == -1 || !found_rotation_point)
	{
		return false;
	}
	
	int str1_index = 1;
	// check if everything after first letter is the start of first str
	for (int i = first_letter_index + 1; i < str2.size(); i++)
	{
		if (!(str1[str1_index] == str2[i]))
		{
			return false;
		}
		
		str1_index++;
	}
	
	// check if everything before first letter is substr of str1
	return isSubStr(str1, str2.substr(0, first_letter_index));
	
}

bool isRotationOptimal(std::string str1, std::string str2)
{
	int len = str1.size();
	if (len == str2.size() && len > 0)
	{
		std::string s1s1 = str1 + str1;
		return isSubStr(s1s1, str2);
	}
	return false;
	
}


int main()
{
	std::string str1 = "aaapl";
	std::string str2 = "apl";
	printf("%s %s %d\n", str1.c_str(), str2.c_str(), isSubStr(str1, str2));
	
	str2 = "aplaa";	
	printf("%s %s %d\n", str1.c_str(), str2.c_str(), isRotation(str1, str2));
	
	printf("%s %s %d\n", str1.c_str(), str2.c_str(), isRotationOptimal(str1, str2));
}