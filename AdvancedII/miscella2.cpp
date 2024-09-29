#include <iostream>
#include <string>
using namespace std;

void findMinMax(float arr[10], float& min, float& max) {
	min = arr[0];
	max = arr[0];
	for (int i = 1; i < 10; i++) {
		if(arr[i] > max) max = arr[i];
		if (arr[i] < min) min = arr[i];
	}
}

int sumOfOdds(int max) {
	int sum = 0;
	for (int i = 2; i <= max; i += 2) {
		sum += i;
	}
	return sum;
}

/*int main() {

	float temperatures[10];
	//cout << "Input temperatures fro 10 days: " << endl;
	for (int i = 0; i < 10; i++) {
		//cin >> temperatures[i];
	}
	float min, max;
	//findMinMax(temperatures, min, max);

	//cout << "Maximalna in minimalna temperatura: " << max << ", " << min;

	int sum = sumOfOdds(26);

	cout << sum;

	return 0;
}*/