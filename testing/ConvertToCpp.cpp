#include <iostream>
#include <vector>
#include "algorithm"


const int N = 40;

void sum(int* p, int n, std::vector<int> d) {
	for (int i = 0; i < n; i++) {
		*p = *p + d.at(i);
	}
}

//int main() {
//
//	//int accum{ 0 };
//	//std::vector<int> data(N, 0);
//
//	//for (int i = 0; i < N; i++) {
//	//	data.at(i) = i;
//	//}
//
//	//sum(&accum, N, data);
//	//std::cout << "Sum is: " << accum;
//
//	int a = 6;
//
//	//std::cout << static_cast<int>(a / 2.0 + 0.5);
//
//	std::vector<int> v = { 1, 15, 3, 4, 5, 3, 3, 2, 5 };
//	auto i = max_element(v.rbegin(), v.rend());
//	//std::cout << *i;
//
//	std::vector<int> myvector;
//
//	myvector.resize(5);
//
//	std::cout << "myvector contains:";
//	for (int i = 0; i < myvector.size(); i++)
//		std::cout << ' ' << myvector[i];
//	std::cout << '\n';
//
//	std::cout << "0 % 5 = " << 0 % 5 << std::endl;
//	std::cout << "4 % 5 = " << 4 % 5 << std::endl;
//	std::cout << "15 % 5 = " << 15 % 5 << std::endl;
//	std::cout << "19 % 5 = " << 19 % 5 << std::endl;
//
//	return 0;
//}