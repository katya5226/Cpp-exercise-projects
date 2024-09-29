#include <iostream>
#include <string>
using namespace std;

//Write a program that asks for two 3x3 Matrix.
//Then the program sums the matrix and stores the result in the first one(A = A + B).
//Then prints on the screen the resulting matrix.

void matrixSum(int m1[3][3], int m2[3][3]) {
	//int sum[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			m1[i][j] = m1[i][j] + m2[i][j];
		}
	}

}

/*int main(void) {

	int matrix1[3][3] = { {2,4,8}, {2,5,1}, {7,5,4} };
	int matrix2[3][3] = { {6,3,2}, {3,4,5}, {7,8,9} };

	matrixSum(matrix1, matrix2);

	for (int i = 0; i < 3; i++) {
		cout << '\n';
		for (int j = 0; j < 3; j++) {
			cout << matrix1[i][j] << '\t';
		}
	}

	return 0;
}*/