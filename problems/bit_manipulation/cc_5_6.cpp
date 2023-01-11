/*
Write a program to swap all odd and even bits in an integer
with as few instructions as possible.
IE, bit 0 and bit 1 are swapped, bit 2 and bit 3 are swapped, and so on.

well we could iterate through the bits, starting at i = 1, going to sizeof(int) * 8, and swap current with previous.
But thats a fair number of instructions.

another option could be we take a copy and do a mask to blank out every other number. starting with 0 index is blanked. 
then we shift it over right.

then we take a copy and do a mask to blank out every other number, starting with index 1 is blanked, and we shift that left.

then we add the two, or do an or.

how do we do the blanking out every other?
we make a binary number like we want it, 0xaaaaaaaa for instance for the 1010 and 0x55555555 for the 0101.




1001 0001

0110 1110
----------------------
1001 0001 & 0101 0101
0

take note of 32 bit integers vs 64 bit integers, but similar logic.

*/

#include <stdio.h>

int swapBits(int num)
{
	
	return ((num & 0xaaaaaaaa) >> 1) | ((num & 0x55555555) << 1);
	
}

int main()
{
	printf("swap of %d is: %d\n", 10, swapBits(10));
	
}