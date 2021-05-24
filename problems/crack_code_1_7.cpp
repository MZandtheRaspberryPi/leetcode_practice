// write an algo, if given MxN matrix, if a value is zero its row and column are set to 0

// what fills matrix? All ints?
// could matrix be zero size?
#include<stdio.h>
#include<vector>
using namespace std;

int *matrix[20];

void setMatrix(int **matrix, int m, int n) {

	for (int i = 0; i < m; i++) {
		matrix[i] = new int[n];
	}

	for (int i = 0; i < m; i++ ) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 1;
		}
	}
	
	matrix[0][8] = 0;
	matrix[15][3] = 0;
	matrix[12][0] = 0;
}

void printMatrix(int **matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", matrix[i][j]);		
		}
		printf("\n");
	}
	printf("\n");
}

void zeroMatrix(int **matrix, int m, int n) {
	// this is O(m + n) storage efficient
	// this is O(2*m*n) time efficient
	vector<int> rows(m, false);
	vector<int> cols(n, false);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			// we found a zero in that col and row previously
			if (cols[j] && rows[i]) {
				continue;
			}
			// this is first zero in column
			else if (matrix[i][j] == 0) {
				rows[i] = true;
				cols[j] = true;
			}
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (rows[i] || cols[j]) {
				matrix[i][j] = 0;
			}
		}
	}
	
}

int main() {
	setMatrix(matrix, 20, 10);
	printMatrix(matrix, 20, 10);
	zeroMatrix(matrix, 20, 10);
	printMatrix(matrix, 20, 10);
}