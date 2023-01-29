/*
Write a function in C called my2DAlloc which allocates a 2 dimensional array.
minimize the number of calls to malloc, and make sure that the memory is accessible
by the notation arr[i][j].

we will use i for rows, and j for columns...

so one approach. we could allocate sizeof(void*) * i memory.
and then allocate j memory i times, and put the pointer to each into i.

but this isnt exactly minimizing the calls to malloc.

if we were to immediately allocate i * j memory,

we could override operators [i][j] on our class.
i would be row, so if we had a 5 x 4 matrix, and we wanted 3,
we would need to go to 5 + 5 + 3th index, 13th index, which is 12.

so this would be index_i_given * (row_num) in, and then for col, .

for the col, we simply do the same to find row, then add in col_num % given j.

then we return this pointer. but, we are in C which doesnt support operator overloading.

so i actually think we do need to do the first approach.

feedback from solution. this works, but to minimize calls to malloc we could add a header in of rows size, 
which points to the array for that rows cols.
then malloc it all at once. plus additional benefit that we can delete it all at once with free.

*/

#include <stdlib.h>

void** my2DAlloc(int num_rows, int num_cols)
{
	void** p1 = (void**)malloc(sizeof(void*) * num_rows);
	for (int i = 0; i < num_rows; i++)
	{
		p1[i] = malloc(sizeof(int) * num_cols);
	}
	return p1;
}


void free2dAlloc(void** p1, int num_rows, int num_cols)
{
	for (int i = 0; i < num_rows; i++)
	{
		void* p2 = p1[i];
		free(p2);
	}
	free((void*)p1);
}

void* my2dAllocOptimal(int num_rows, int num_cols)
{
	int i;
	int header = num_rows * sizeof(int*);
	int data = num_rows * num_cols * sizeof(int*);
	int** rowptr = (int**)malloc(header+data);
	if (rowptr == NULL) return NULL;
	
	int* buf = (int *) (rowptr + num_rows);
	for (i = 0; i < num_rows; i++)
	{
		rowptr[i] = buf + (i * num_cols);
	}
	return rowptr;
}

int main()
{
	void** p1 = my2DAlloc(5, 4);
	free2dAlloc(p1, 5, 4);
}