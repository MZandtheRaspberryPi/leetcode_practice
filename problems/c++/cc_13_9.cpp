/*
Write an aligned malloc and free functino that supports allocating memory
such that the memory address returned is divisible by a specific power of 2.

allign_malloc(1000, 128) will return a memory address that is a multiple of 128
and that points to memory of size 1000bytes.

aligned_free() will free memory allocated by allign_malloc.

one brutal approach would be to alloc memory and check the addres, perhaps casting the pointer to an integer and checking 
for mutiple, if not, try again, and then free the stuff you already checked.

another way would be to get an integer pointer, check the address, and see what you need to add to that to get to the next
 multiple of 128.

still no guarantee tho that some other process wont grab that address.

I guess another approach would be to alloc a bigger amount than you need, then free a smaller amount.

how do memory addresses work? Are they each one byte? so like sequentially? or depends on architecture 32 bit vs 64 bit perhaps?

feedback from solution:
the best way is to reserve more memory than we need, so that we can then find one address in there that will be divisible by the input.
that said, when we return an address in the middle, we also have to then somehow remember the first one we allocated so that we can free it.

for the how much do we allocate, we allocate size requested + sizeof(void*) + the requested_pow_2_diviser - 1.
For where we start, we can actually take the starting pointer, and add sizeof(void*) and requested pow_2_divisor, and then do 
bitwise and with a mask.

the mask will be the requested pow_2_divisor - 1, which will give all ones from the bit to the right of power of 2, and not it.
so we have, for 16, 15, notted, is 1111 0000.
then if we and this with our starting pointer plus buffer, we will zero out the digits and make sure it ends on that power of 2.
so we can use this as our new start.

but, now we need to store original pointer so we can free it. so treet p2 as a void **, an array of pointers, and set idnex - 1 to be 
the p1 pointer.

then the free function will look for that index and free it.


*/
#include <iostream>

void* allign_malloc(size_t requested_buffer, size_t pow_2_divisor)
{
	void* p1 = malloc(requested_buffer + pow_2_divisor - 1 + sizeof(void*));
	if (p1 == nullptr) return p1;
	
	void* p2 = (void*)(((size_t)p1 + pow_2_divisor - 1 + sizeof(void*)) & (~(pow_2_divisor - 1)));
	
	((void**)p2)[-1] = p1;
	return p2;
	
}

void aligned_free(void* p2)
{
	void* p1 = ((void**)p2)[-1];
	free(p1);
	
}

int main()
{
	int* buffer1 = (int*)malloc(4 * sizeof(int));
	int* buffer2 = (int*)malloc(2 * sizeof(int));
	int* buffer3 = (int*)malloc(2 * sizeof(int));
	
	std::cout << "in'ot size" << sizeof(int) << std::endl;
	std::cout << buffer1 << std::endl;
	std::cout << buffer2 << std::endl;
	std::cout << buffer3 << std::endl;
	
	std::cout << (long long)buffer1 << std::endl;
	std::cout << (long long)buffer2 << std::endl;
	std::cout << (long long)buffer3 << std::endl;
	
	// it looks like the memory address is hexadecimal, and when cast to long long, we can see a number
	// note pointers 64 bit on windows.
	
	// so my first memory address should be for 4 * 4 bytes, which is 16 bytes.
	// I see the difference between it and the next memory address, which should hold 2 * 4 bytes, 8 bytes, is 
	// 32 bytes.
	
	free(buffer1);
	free(buffer2);
	free(buffer3);
	
	void* p2 = allign_malloc(1000, 32);
	std::cout << p2 << std::endl;
	
	std::cout << (long long)p2 << std::endl;
	aligned_free(p2);
	
	
}