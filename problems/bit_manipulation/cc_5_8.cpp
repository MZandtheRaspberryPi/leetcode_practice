/*
A monochromatic screen is stored as a single array of bytes, 
allowing 8 consecutive pixels to be stored in one byte.
screen has width w, where w divisble by 8, no byte will be split across rows.

height of screen, derivced from length of array and width.

implement a funcion drawHorizontalLine(byte[] screen, int width, int x1, int x2, int y)
which draws horizontal line from x1, y to x2, y.

what shall we do if someone passes in an x2 - x1 that is longer than width? bound it.

first, we calculate starting and ending point of the line, in terms of indices in screen.

starting point would be x1 / 8. the remainder, x1 % 8, is the within byte index.
ending point would be x2 / 8. the remainder, x2 % 8 is the within byte index.

then we need to fill the starting byte. for this, we will shift a 1 bit to the left of the index we need it to start at, and subtract one.
then we will or this with the byte there.

for the ending byte, we will shift a one to the index we want to end on, and then subtract one, then not it. then we will or this with the byte there.

for all the bytes in between we will or with ~0.

*/

#include <cstdint>
#include <stdio.h>

#define WIDTH 128
#define HEIGHT 64


#define ARR_LENGTH WIDTH * HEIGHT / 8


/*
    x   
 ------
|      |  y
|      |
 ------

*/

int drawHorizontalLine(std::uint8_t* screen, unsigned int screen_length, unsigned int width, unsigned int  x1, unsigned int x2, unsigned int y)
{
	unsigned int height = screen_length * 8 /width;
	
	if (y >= height)
	{
		return -1;
	}
	
	if (x1 >= width || x2 >= width)
	{
		return -2;
	}
	
	unsigned int line_length = x2 - x1;
	
	unsigned int screen_width_bytes = width / 8;
	
	if ((x1 + line_length) >= width)
	{
		return -3;
	}
	// for whatever row we are in, add that many bytes to index
	unsigned int starting_array_index = 0;
	starting_array_index += y * screen_width_bytes;
	starting_array_index += x1 / 8;
	std::uint8_t starting_within_byte_lsb_offset = (8 - (x1 % 8));
	
	// if we have 30, we will have 6 modded. so we need to start the line after 6 bytes.
	
	// change starting byte
	std::uint8_t mask = ((1 << (starting_within_byte_lsb_offset)) - 1);
	screen[starting_array_index] = screen[starting_array_index] | mask;
	
	unsigned int ending_array_index = 0;
	ending_array_index += y * screen_width_bytes;
	ending_array_index += x2 / 8;
	unsigned int ending_within_byte_index = (8 - (x2  % 8));
	mask = ~((1 << ending_within_byte_index) - 1);
	screen[ending_array_index] = screen[ending_array_index] | mask;
	
	for (unsigned int array_runner = starting_array_index + 1; array_runner < ending_array_index; array_runner++)
	{
		screen[array_runner] = (screen[array_runner] | (~0));
	}
	
	return 0;

}

bool getBit(std::uint8_t num, int index)
{
	int mask = 1 << index;
	return (num & mask) != 0;
	
}


void print(std::uint8_t* screen, unsigned int screen_length, unsigned int width)
{
	int line_length = width / 8;
	for (int i = 0; i < screen_length; i++)
	{
		if (i % line_length == 0)
		{
			printf("\n");
		}
		
		for (int j = 7; j >= 0; j--)
		{
			if (getBit(screen[i], j))
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
	}
	printf("\n");
}

int main()
{
	std::uint8_t arr[ARR_LENGTH];
	for (int i = 0; i < ARR_LENGTH; i++)
	{
		arr[i] = 0;
	}
	print(arr, ARR_LENGTH, WIDTH);
	
	printf("arr length %d, width %d \n", ARR_LENGTH, WIDTH);
	int ret = drawHorizontalLine(arr, ARR_LENGTH, WIDTH, 30, 70, 5);
	printf("return is %d\n", ret);
	print(arr, ARR_LENGTH, WIDTH);
	
	
}