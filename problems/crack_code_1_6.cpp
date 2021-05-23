#include<stdio.h>
#include<vector>
using namespace std;

int matrix[20][20];

void clearMatrix(int matrix[20][20]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			matrix[i][j] = 0;
		}
	}
}

void setMatrix(int matrix[20][20]) {
	clearMatrix(matrix);
	for (int i = 0; i < 20; i++) {
		//matrix[i][i] = 1;
		matrix[0][i] = i;
	}
	for (int i = 1; i < 20; i++) {
		matrix[i][0] = i;
	}
}

void setMatrixI(int matrix[20][20]) {
	clearMatrix(matrix);
	for (int i = 0; i < 20; i++) {
		matrix[i][i] = 1;
	}
}

void setMatrixSeq(int matrix[20][20]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			matrix[i][j] = j;
		}
	}
}

void printMatrix(int matrix[][20]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			printf("%d ", matrix[i][j]);		
		}
		printf("\n");
	}
	printf("\n");
}

void rotateMatrix(int matrix[20][20], int N) {
	// if we have a 3x3 matrix, we go layer by layer through outer layers to inner.
	// memorize, top, bottom, left, right, and then rotate setting. Then go to the next layer.
	// with a 3x3 matrix we only have one layer, the outer layer
	// [1, 0, 0,
	//  0, 1, 0,
	//  0, 0, 1]
	// our algo has to rotate each side. let's start outside, then go inside. we'll need n / 2 rotations

	// this will result in O(n) storage, (O(4n) actually which is bad), and o(N^2) time as we have to touch each point
	vector<int> upper(N, 0);
	vector<int> lower(N, 0);
	vector<int> left(N, 0);
	vector<int> right(N, 0);

	int numberShifts = N / 2;

	for (int shiftNum = 0; shiftNum < numberShifts; shiftNum++) {
		// memorizing matrix that we'll shift
		for (int i = shiftNum; i < N - shiftNum; i++) {
			upper[i] = matrix[shiftNum][i];
			lower[i] = matrix[N - 1 - shiftNum][N - 1 - i];
			left[i] = matrix[N - 1 - i][shiftNum];
			right[i] = matrix[i][N - 1 - shiftNum];
		}

		for (int i = shiftNum; i < N - shiftNum; i++) {
			// setting upper
			matrix[shiftNum][i] = left[i];
			// setting right
			matrix[i][N - 1 - shiftNum] = upper[i];
			// setting lower
			matrix[N - 1 - shiftNum][N - 1 - i] = right[i];
			// setting left
			matrix[N - 1 - i][shiftNum] = lower[i];
		}
	}
}


void rotateMatrixOptimal(int matrix[][20], int N) {
	int numberLayers = N / 2;
	for (int layerNum = 0; layerNum < numberLayers; layerNum++) {
		int tmp;
		// if a row has 20 entries, we only need to swap 19 times, and the last swap
		// will be the first of every row, so we start at index + 1
		for (int i = layerNum + 1; i < N - layerNum; i++) {
			tmp = matrix[layerNum][i];
			// top gets set to left
			matrix[layerNum][i] = matrix[N - 1 - i][layerNum];
			// left gets set to bottom
			matrix[N - 1 - i][layerNum] = matrix[N - 1 - layerNum][N - 1 - i];
			// bottom gets set to right
			matrix[N - 1 - layerNum][N - 1 - i] = matrix[i][N - 1 - layerNum];
			// right gets set to top
			matrix[i][N - 1 - layerNum] = tmp;
		}
	}
}

int main() {
	setMatrix(matrix);
	printMatrix(matrix);
	rotateMatrix(matrix, 20);
	printMatrix(matrix);

	setMatrixI(matrix);
	printMatrix(matrix);
	rotateMatrix(matrix, 20);
	printMatrix(matrix);

	setMatrixSeq(matrix);
	printMatrix(matrix);
	rotateMatrix(matrix, 20);
	printMatrix(matrix);

	setMatrix(matrix);
	printMatrix(matrix);
	rotateMatrixOptimal(matrix, 20);
	printMatrix(matrix);

	setMatrixSeq(matrix);
	printMatrix(matrix);
	rotateMatrixOptimal(matrix, 20);
	printMatrix(matrix);
}