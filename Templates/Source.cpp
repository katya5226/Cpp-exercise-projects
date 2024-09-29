#include <iostream>
#include <vector>

template <typename T>
inline void const Print(std::vector<T> const &v) {
	for (int i = 0; i < v.size(); i++) {
		std::cout << v.at(i) << '\n';
	}
}

template <>
inline void const Print(std::vector<size_t> const& v) {
	std::cout << "This is a SIZE_T vector!";
}

template <typename T, typename U>
T afunction(std:: vector<T> const &v1, std::vector<U> const& v2) {
	size_t l1 = v1.size();
	size_t l2 = v2.size();
	if (l1 < l2) { return v1.at(0); }
	else return v1.at(1);
}


/*int main() {

	std::vector<float> myVector = { 3,4,5,6,2,8 };
	std::vector<size_t> anotherVector = { 3,4,5,6,2,8 };

	//std::vector<int>* myVector = new std::vector<int>(10);

	Print(myVector);
	Print(anotherVector);

	std::cout << afunction(myVector, anotherVector);

	//delete(myVector);

	return 0;
}*/