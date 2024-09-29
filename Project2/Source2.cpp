#include <iostream>
using namespace std;

class Box {
	double width{ 0 };

public:
	Box() {}

	void setWidth(double x) {
		width = x;
	}

	friend void printWidth(Box);
};

void printWidth(Box b) {
	cout << b.width;
}

int power(int a, int b) {
	int p = 1;
	for (int i = 0; i < b; i++) {
		p *= a;
	}
	return p;
}

int arr[6] = { 1,2,3,4,5,6 };

void relocate_print(int in, int array[6], int nu) {
	for (int u = 6; u > in; u = u - 1) {
		array[u] = array[u - 1];
	}

	array[in] = nu;

	for (int i = 0; i <= 6; i++) {
		cout << array[i] << "\n";
	}
	return;
}


int main() {
	
	/*int myArray[6] = {1,2,3,4,5,6};
	int* myArrayP = myArray;
	int x;
	int y;

	cout << "Enter an integer and an index: ";
	cin >> x >> y;

	const int index = y;

	if (0 <= index < 6) {
		int newArray[7];
		newArray[index] = x;
		for (int i = 0; i < index; i++) {
			newArray[i] = myArray[i];
		}
		for (int i = index + 1; i < 7; i++) {
			newArray[i] = myArray[i-1];
		}
		myArrayP = newArray;
		for (int i = 0; i < 7; i++) {
			cout << '\n' << *(myArrayP + i) ;
		}
	}*/

	int num; int index;
	cout << "Enter a number:";
	cin >> num;
	cout << "Enter index:";
	cin >> index;

	relocate_print(index, arr, num);

	return 0;
}
