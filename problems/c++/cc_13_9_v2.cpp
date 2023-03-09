/*
write function that supports allocating memory such that address is divisible by a power of 2.
ex
align_malloc(1000, 128) returns memory address divisble by power of 128, and that points to mem of size 1000 bytes.
align_free() frees mem.

so lets say our power of 2 is 8.

we need to allocate so much space, so that we definitely have a starting point in that range that will have a multiple of 8
in it, and x bytes after that.

if x is 4.

we need to allocate 7 bytes, so that whereever the starting mem is, we can find a starting multiple of 8.
then we need to allocate 4 bytes for x.
then we also need to store a void pointer to the original memory block so we can free it all. we could do this in 4 bytes
before the address we want.

to get the blcck, we could do a bit mask.

we want to take the mem address we got, and add the offset to it from the divisor.
then we can make a mask by taking ~(divisor - 1), which will give us 1s from pow of 2 onward and 0s after.
we and our target with that to zero the bits to that pow of 2.

8 in binary is:

1000

to make dividable by 8.

we need to zero out bit index 0 1 2.

*/

#include <iostream>

void* allign_malloc(int num_bytes, int divisor)
{
	int offset = divisor - 1 + sizeof(void*);
	void* block_start = malloc(sizeof(void*) + num_bytes + offset);
	void* block_divisible_start = (void*)(((size_t) block_start + offset) & ~(divisor - 1));
	void** block_runner = (void**)block_divisible_start;
	block_runner[-1] = block_start;
	return block_divisible_start;
	
}

void allign_free(void* mem_block)
{
	void** mem_block_runner = (void**)mem_block;
	mem_block_runner--;
	free(*mem_block_runner);
}

int main() {
	
	void* mem_block = allign_malloc(1000, 128);
	std::cout << (size_t)mem_block << std::endl;
	allign_free(mem_block);
}
