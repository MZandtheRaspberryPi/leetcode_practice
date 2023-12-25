/*
a magic index is defined, to be an index such that A[i]= i. i =0 to n-1.

given a sorted array, write a method to find a magic index, if one exists, in array A.

Follow up, what if values not distinct?


ideas: binary search varient, we want to find just one. take in low and high, if low is greater than high return error.

if index is less than than value, search lower part. if index is greater than value, search upper part.
if index equal value, return it.

should take logn time. and log n memory.

if sorted move up bottom or upper index until get off of value.


*/
#include <cstdint>
#include <iostream>
#include <vector>

typedef std::vector<int32_t> array_t;

array_t prepare_sorted_arr()
{
	array_t my_arr(7, 0);
	my_arr[0] = -1;
	my_arr[1] = 0;
	my_arr[2] = 2;
	my_arr[3] = 4;
	my_arr[4] = 8;
	my_arr[5] = 11;
	my_arr[6] = 15;
	return my_arr;
}

void print_arr(const array_t& my_arr)
{
	for (size_t i = 0; i < my_arr.size(); i++)
	{
		if (i == my_arr[i])
		{
			std::cout << "magic_index: " << i << " val: " << my_arr[i] << std::endl;
		}
	}
}

int32_t search_sorted_arr(const array_t& my_arr, const uint32_t low, const uint32_t high)
{
	std::cout << "low " << low << " high: " << high << std::endl;
	if (low > high)
	{
		return -1;
	}
	
	int32_t mid_index = (high + low) / 2;
	
	int32_t val = my_arr[mid_index];
	
	if (val == mid_index)
	{
		return mid_index;
	}
	else if (val > mid_index)
	{
		return search_sorted_arr(my_arr, low, mid_index - 1);
	}
	else
	{
		return search_sorted_arr(my_arr, mid_index+1, high);
	}
}

void find_magic_index(const array_t& my_arr)
{
	int32_t magic_num = search_sorted_arr(my_arr, 0, my_arr.size() - 1);
	if (magic_num != -1)
	{
		std::cout << "algo found magic num: " << magic_num << std::endl;
	}
	return;	
}



int main()
{
	array_t my_arr = prepare_sorted_arr();
	print_arr(my_arr);
	find_magic_index(my_arr);
	
	
}