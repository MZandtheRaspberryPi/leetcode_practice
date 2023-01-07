/*
Given a real number between 0 and 1, eg 0.72, that is passed in as a double,
print the binary representation. if the number cannot be represented accurately in binary with less than 32 characters print error.

what is the binary representation of a real number?

0.101base2 is 1 * (1/(2^1)) + 0 * (1/(2^2)) + 1 * (1/(2^3))

so we can shift the fractional sum by multiplying by 2. and check if its greater than 1. if so, we know the digit
to the right of zero was a 1.

or alternatively compare to fractional 0.5, then 0.25, and onwards.
*/

#include<stdio.h>
#include <string>

std::string doubleRealToBinaryStr(double x)
{
	if (x >= 1 || x <= 0)
	{
		return "error";
	}
	
	std::string binary_string = "";
	double frac = 0.5;
	
	while (x > 0)
	{
		printf("looping\n");
		if (binary_string.size() > 32)
		{
			return "error";
		}
		
		if ( x >= frac )
		{
			binary_string += "1";
			x -= frac;
		}
		else
		{
			binary_string += "0";
		}
		
		frac = frac / 2;
	}
	return binary_string;
}

int main()
{
	printf("%s\n", doubleRealToBinaryStr(0.75).c_str());
}