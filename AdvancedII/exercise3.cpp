#include <iostream>
#include <string>
using namespace std;

class Rectangle {
	double a, b;
public:
	Rectangle(double x, double y) : a(x), b(y) {};
	double area() {
		double S = a * b;
		return S;
	}
	friend void duplicate(Rectangle&);
	//friend void duplicate(const Rectangle&);
};

void duplicate(Rectangle& rect) {
	rect.a *= 2;
	rect.b *= 2;
}

/*Rectangle duplicate(const Rectangle& param)
{
	Rectangle res;
	res.a = param.a * 2;
	res.b = param.b * 2;
	return res;
}*/

/*int main() {

	Rectangle myRect(2.4, 2.8);

	cout << "myRect area: " << myRect.area() << endl;

	duplicate(myRect);

	cout << "myRect-duplicated area: " << myRect.area() << endl;

	return 0;
}*/