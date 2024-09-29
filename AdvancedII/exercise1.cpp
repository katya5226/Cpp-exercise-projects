#include <iostream>
#include <string>
using namespace std;

//Write a program that enumerate some auto's brands.
//Then create a variable called my_car_brand and make it equal to one of them.
//Print a message saying hello to the user.

enum brand_x {FIAT, VOLVO, OPEL, SAAB, CITROEN, TOYOTA};
void print_brand(const brand_x brand) {
	const char* names[] = { "FIAT", "VOLVO", "OPEL", "SAAB", "CITROEN", "TOYOTA" };
	cout << names[brand];
}

/*int main() {

	string sentence;
	//getline(cin, sentence);
	//cout << '\n' << sentence; 
	brand_x carBrand = OPEL;
	print_brand(carBrand);

	return 0;
}*/