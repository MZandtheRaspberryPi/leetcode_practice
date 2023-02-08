/*
Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

Input: num1 = "2", num2 = "3"
Output: "6"

Input: num1 = "123", num2 = "456"
Output: "56088"

idea. do multiplication like a human would. start with lowest digit, convert to int by subtracting '0'.

carry the 10s. then do addition.

so for each digit in smaller number, will have to touch each digit in the larger number.
then we will have to add them together, which will go through digits once more.

so if both nums have 5 digits, we will go through 5 * 5 + 5 operations.
so roughly O(N*M) where N is length string 1, M length string 2.

in space, we will take O(N + M) to store result string.


*/

#include <stdio.h>
#include <string>


std::string multiply(std::string num1, std::string num2) {
	std::string result_str;
	result_str.resize(num1.size() + num2.size());
	for (int i = 0; i < result_str.size(); i++)
	{
		result_str[i] = '0';
	}
	
	// start w/ smaller string
	std::string* smaller_str = num1.size() > num2.size() ? &num2 : &num1;
	std::string* bigger_str = num1.size() > num2.size() ? &num1 : &num2;

	int carry = 0;
	for (int i = smaller_str->size() - 1; i >= 0; i--)
	{
		carry = 0;
		int digit_small = (*smaller_str)[i] - '0';
		for (int j = bigger_str->size() - 1; j >= 0; j--)
		{
			int digit_big = (*bigger_str)[j] - '0';
			int tmp = digit_small * digit_big;
			tmp = tmp + carry;
			carry = 0;
			int cur_digit = result_str[j + i + 1] - '0';
			tmp = tmp + cur_digit;
			result_str[i + j + 1] = '0' + tmp % 10;
			carry = tmp / 10;
		}
		result_str[i] = result_str[i] + carry;
		carry = 0;
	}
	
	// trim zeros
	int zero_ctr = 0;
	for (int i = 0; i < result_str.size(); i++)
	{
		if (result_str[i] == '0')
		{
			zero_ctr++;
		}
		else
		{
			break;
		}
	}
					if (result_str.size() != zero_ctr)
					{
							return result_str.substr(zero_ctr);
					}
					else
					{
							return "0";
					}
	return result_str;
}


int main()
{
	multiply("123", "456");
}