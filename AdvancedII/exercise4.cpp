#include <iostream>
#include <string>
using namespace std;


class Box {
	double width;
public:
	Box(double w) : width(w) {};
	friend void printWidth(const Box&);
};

void printWidth(const Box& myBox) {
	cout << myBox.width;
}

/*int main() {

	Box aBox(55.7);
	printWidth(aBox);

	return 0;
}*/