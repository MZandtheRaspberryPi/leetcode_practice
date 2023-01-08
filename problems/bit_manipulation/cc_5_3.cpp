/*
Given a positive integer, print the next smallest and the next largets number
that have the same number of 1 bits in their binary representation.

could just iterate up till we find the num, then iterate down perhaps. but time complexity likely bad.

alternatively, could flip a 1 and a zero.

for larger num, could find the first zero with ones to the right of it, looking from least sig bit.
flip that.

then we want to change one of the ones to a zero, while shrinking the number as much as we can.

clear everything to the right of the original point, then put back in one less one than you had, all on the right, and the rest of the zeros.

For smallest bigger than number, we can flip bits perhaps?
we want to move perhaps the smallest bit we can to the left. so add a 1 somewhere where there currently is a zero.
ideally from least sig bit to most sig bit, we put a 0 where a 1 is, and then later on a 1 where a zero is.

How do we count bits tho...we could do a get function.

*/

#include <stdio.h>
#include <utility>

bool getBit(int num, int i)
{
	int mask = 1 << i;
	return (mask & num) != 0;
}

int getNumberOf1s(int num)
{
	int count = 0;
	for (size_t i = 0; i < sizeof(num) * 8; i++)
	{
		if (getBit(num, i))
		{
			count++;
		}
	}
	return count;
}

// pair.first is the lower neighbor, pair.second is the higher neighbor
std::pair<int, int> getNearestSame1sNumber(int target_number)
{
	std::pair<int, int> result;
	int bits_in_target = getNumberOf1s(target_number);
	int runner = target_number - 1;
	int found_nearest_match = false;
	while (bits_in_target != getNumberOf1s(runner))
	{
		runner--;
	}
	result.first = runner;
	runner = target_number + 1;
	
	while (bits_in_target != getNumberOf1s(runner))
	{
		runner++;
	}
	result.second = runner;
	return result;
}

int getNextOptimal(int num)
{
	// get c0 and c1
	int c = num;
	int c0 = 0;
	int c1 = 0;
	
	while (((c & 1) == 0) && (c != 0))
	{
		c0++;
		c >>= 1;
	}
	
	while ((c & 1) == 1)
	{
		c1++;
		c >>= 1;
	}
	
	// error if n == 11..1100...00 no bigger number w/ same number of ones...
	if (c0 + c1 == 31 || c0 + c1 == 0)
	{
		return -1;
	}
	
	// position of right most trailing zero
	int p = c0 + c1;
	
	// flip rightmost non-trailing zero
	num |= (1 << p);
	
	num &= ~((1 << p) - 1); // clear all bits to right of p
	num |= (1 << (c1 - 1)) - 1; // insert c1 - 1 ones on the right;
	return num;
}

int getPrevOptimal(int num)
{
	int temp = num;
	int c0 = 0;
	int c1 = 0;
	while (((temp & 1) == 1) && (temp != 0))
	{
		c1++;
		temp >>= 1;
	}
	
	if (temp == 0) return -1;
	
	while ((temp & 1) == 0 && (temp != 0))
	{
		c0++;
		temp >>= 1;
	}
	
	int p = c0 + c1; // position of rightmost non-trailing one
	num &= ((~0) << (p + 1)); // clears from bit p onwards.
	
	int mask = (1 << (c1 + 1)) - 1; // sequence of (c1 + 1) ones
	num |= mask << (c0 - 1);
	return num;
}

int main()
{
	std::pair<int, int> result;
	result = getNearestSame1sNumber(1024);
	printf("%d: %d %d\n", 1024, result.first, result.second);
	
	printf("%d: %d %d\n", 1024, getPrevOptimal(1024), getNextOptimal(1024));
	
}