/*
given image represented by n by n matrix, where each pixel in image
is 4 bytes, write method to rotate image by 90 degrees. can you do it in place?

well, which way we rotating, so that top row becomes right column?

we will need to keep one 

a b c d
e f g h
i j k l
m n o p

remember a.
put m > a, p > m, d > p, tmp > d

a b c d e
f g h i j
k l m n o
p q r s t
u v w x y

if we have a four matrix, we have 2 square lines to do. 
if we have a5 matrix, have 2 square lines to do.

so for i = 0, i < n / 2.


so, col_index, row_index. col_index is what index inside a column. set it to n - 1. row_index inside a row which one we switching out. set it to 0

while (

*/
#include <stdio.h>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

void printM(Matrix m);

void rotate(Matrix& matrix)
{
	const int N = matrix.size();
	printM(matrix);
	for (int outer_square_index = 0; outer_square_index < N / 2; outer_square_index++)
	{
		
		int within_side_index = outer_square_index;
		
		while (within_side_index < N - 1 - outer_square_index)
		{
			int tmp = matrix[outer_square_index][within_side_index];
			matrix[outer_square_index][within_side_index] = matrix[N - 1 - within_side_index][outer_square_index];
			matrix[N - 1 - within_side_index][outer_square_index] = matrix[N - 1 - outer_square_index][N - 1 - within_side_index];
			matrix[N - 1 - outer_square_index][N - 1 - within_side_index] = matrix[within_side_index][N - 1 - outer_square_index];
			matrix[within_side_index][N - 1 - outer_square_index] = tmp;
			
			within_side_index++;
			//printf("%d, %d\n", within_side_index, outer_square_index);
			// printM(matrix);
		}
	}
	printM(matrix);
}

void printM(Matrix m)
{
	printf("\n");
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			printf("%d", m[i][j]);
			printf("  ");
		}
		
		printf("\n");
	}
	printf("\n");
}

int main()
{
	
	std::vector<std::vector<int>> m;
	
	int N = 3;
	
	m.resize(N);
	for (int i = 0; i < N; i ++)
	{
		std::vector<int> row;
		row.resize(N);
		m[i] = row;
	}
	
	
	int counter = 0;
	for (int i = 0; i < N; i ++)
	{
		for (int j = 0; j < N; j++)
		{
			m[i][j] = counter;
			counter ++;
		}
	}
	
	rotate(m);
	
	
	N = 5;
	
	m.resize(N);
	for (int i = 0; i < N; i ++)
	{
		std::vector<int> row;
		row.resize(N);
		m[i] = row;
	}
	
	
	counter = 0;
	for (int i = 0; i < N; i ++)
	{
		for (int j = 0; j < N; j++)
		{
			m[i][j] = counter;
			counter ++;
		}
	}
	
	rotate(m);
	
	N = 6;
	
	m.resize(N);
	for (int i = 0; i < N; i ++)
	{
		std::vector<int> row;
		row.resize(N);
		m[i] = row;
	}
	
	
	counter = 0;
	for (int i = 0; i < N; i ++)
	{
		for (int j = 0; j < N; j++)
		{
			m[i][j] = counter;
			counter ++;
		}
	}
	
	rotate(m);
	
	/*
	0 1 2
	3 4 5
	6 7 8
	*/
	
	
}
