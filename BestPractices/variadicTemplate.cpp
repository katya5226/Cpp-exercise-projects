/*#include<iostream>

template<typename T>
T summer(T a) {
	return a;
}

template<typename T, typename... Args>
T summer(T a, Args... args) {
	return summer(args...) + a;
}

int main() {

	int sum = summer(1, 2, 3, 4, 5);

	std::cout << sum;
	return 0;
}*/