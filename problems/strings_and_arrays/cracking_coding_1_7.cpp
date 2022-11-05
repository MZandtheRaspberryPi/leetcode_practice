/* 

write an algo such that if a 0 is in a matrix, its entire row and column are set to zero

we could visit each entry in matrix, check if zero and if so check row and col and set to zero. then continue.
but here we revisit places we previously set to 0. how could we do this better?

we could take some storage. one row for cols, one row for rows.
if we find one we set bool there to true. then on each loop, we check if not row or col and continue. save a bit for some storage.

storage O(N)
time O(N) in worst case where no zeros. if all zeros, should just visit one row but still O(N)

feedback, missed that we are modifying in place and could affect loops in the future. so instead, loop through set rows/cols.
then loop through once more and set to 0 if row/col.
*/
#include <stdio.h>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

void printM(const Matrix& m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[0].size(); j++)
		{
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void setToZero(Matrix& m)
{
	if (m.size() == 0)
	{
		return;
	}
	
	std::vector<bool> rows(m.size(), false);
	std::vector<bool> cols(m[0].size(), false);
	
	for (int i = 0; i < rows.size(); i++)
	{
		for (int j = 0; j < cols.size(); j++)
		{
			if (m[i][j] == 0)
			{
				rows[i] = true;
				cols[j] = true;
			}
		}
	}
	
	for (int i = 0; i < rows.size(); i++)
	{
		for (int j = 0; j < cols.size(); j++)
		{
			if (rows[i] || cols[j])
			{
				m[i][j] = 0;
			}
		}
	}
}




int main()
{
	
	int N = 6;
	
	Matrix m;
	m.resize(N);
	
	for (int i = 0; i < m.size(); i++)
	{
		std::vector<int> row;
		row.resize(N);
		m[i] = row;
	}
	
	int counter = 0;
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			m[i][j] = counter;
			counter++;
		}
	}
	
	m[0][3] = 0;
	m[4][0] = 0;
	
	m[2][1] = 0;
	
	printM(m);
	
	setToZero(m);
	
	printM(m);
	
	
	
}