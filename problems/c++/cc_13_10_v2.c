/*

write a function in C to allocate a 2d array. Make sure it can be used with the arr[i][j] syntax.

and, minimize the number of calls to malloc

well, we could malloc i. and then loop over i and malloc j and put it into i. But this would be a lot of calls to malloc.
specifically, would be i*j malloc calls

alternatively, a 2d array can also be represented by one long 1d array.

we could malloc all of that, plus a header row to point to the actual data. Then we just have to be careful about indices.

we cast it to a void**. Then, from int t = 0, t < i, we put a pointer to the row we want.
specifically, we set start[i] = start[i*j].


one call to malloc. 

time complexity to allocate:
O(i) where i is the number of rows.
space complexity O(i*j) where i is rows and j is columns.

mistakes, when setting the row indices, didnt cast to int* before setting.
Also, didnt account to skip header row when assigning.

*/
#include <stdio.h>
#include <stdlib.h>

int** alloc_2d_arr(int num_rows, int num_cols)
{
	size_t bytes_to_alloc = ((num_rows * num_cols) * sizeof(int*)) + num_rows*sizeof(int*);
	int** mem_start = (int**)malloc(bytes_to_alloc);
	if (mem_start == NULL) return NULL;
	
	
	
	for (int i = 0; i < num_rows; i++)
	{
		mem_start[i] = (int*)(mem_start[(num_rows + 1) * num_cols]);
	}
	
	return mem_start;
	
}

void free_2d_arr(int** mem_start)
{
	free(mem_start);
}

int main()
{
	int** arr_2d_ptr = alloc_2d_arr(5, 7);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			int* row_loc = arr_2d_ptr[i];
			row_loc[j] = 0;
		}
	}
	
	free_2d_arr(arr_2d_ptr);
	
}