#include <iostream>
#include <string>
using namespace std;

class Dog {
private:
	string dogName;
	//int dogAge;

public:
	string getDogName() {
		return dogName;
	}

	void setDogName(string name) {
		dogName = name;
	}

};

/*int main() {

	Dog Tim;
	Tim.setDogName("Tim");
	cout << Tim.getDogName();
	//std::cout << "Enter a number: ";
	//int x{};
	//std::cin >> x;
	//std::cout << "You entered " << x << "\nDouble that number is: " << 2*x;

	return 0;
}*/
