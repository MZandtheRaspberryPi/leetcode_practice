/*
You are given 2 32-bit numbers, N and M, and two bit postions, i and j. Write a method to insertM into N such that M starts at bit j and ends at bit i.
You can assume that bits j through i have enough space to fit all of M.

That is, if M=10011, you can assume there are at least 5 bits between j and i. You would not,
for example, have j = 3 and i = 2, because M could not fully fit between bit 3 and bit 2.

Input N =  10000000000 M = 10011, i = 2, j = 6

output N = 10001001100

So we could clear the bits between i and j in N. Then we can shift M over to the left till there are two zeros before it. Then do an OR 


*/

#include <cmath>
#include <stdio.h>

// starting index here is from the least signficant bit, ending_index inclusive from least sig bit
int clearNBits(int num, int starting_index, int ending_index)
{
	int ones = !0;
	int mask_from_most_sig_bit = ~ones << (starting_index + 1); // starting index of 6 means that 7 zeros from least sig bit onward. so index 7 is a 1.
	int mask_from_least_sig_bit = ((1 << starting_index) - 1);
	int mask = mask_from_most_sig_bit | mask_from_least_sig_bit;
	return num & mask;
	
}

int insertNum(int N, int M, int starting_index, int ending_index)
{
	int cleared_N = clearNBits(N, starting_index, ending_index - starting_index + 1);
	// shift M so that its most significant digit is at starting index
	int m_shifted = M << ending_index;
	printf("%d\n",m_shifted);
	return cleared_N | m_shifted;
}


int main()
{
	printf("%d\n", clearNBits(0b10000000000, 6, 5));
	printf("%d\n", 0b10011 << 6);
	printf("%d\n", clearNBits(0b1111111, 5, 4));
	printf("%d\n", insertNum(0b10000000000, 0b10011, 6, 2));
	
}