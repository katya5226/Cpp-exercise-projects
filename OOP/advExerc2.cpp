#include <iostream>
using namespace std;

void reader(const char a[], const int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}

void modifier(char a[], const int n) {
	for (int i = 0; i < n; i++) {
		a[i] = 'O';
		cout << a[i] << " ";
	}
}

template <typename T>
struct Table {
	const int n;
	T* p;

	Table(const int x) : n(x) {
		p = new T[n];
	}
	~Table() { delete[] p; }
	T& operator [](int i) { return p[i];}
};

int main() {

	char myArray[5] = { '1','2','3','4','5' };
	//reader(myArray, 5);

	int rows[3] = {1,2,3};
	int cols[5] = { 7,45,21,46,23 };

	Table<int> myTable(5);
	myTable[0] = 5;
	myTable[1] = 14;

	cout << myTable[0];

	char* ex1;
	char** ex2;
	char* ex3[10];
	char(*ex4)[30];
	char(*ex5[10])[500];
	//int* const ex6;
	const int* ex7;

	return 0;
}