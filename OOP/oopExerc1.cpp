#include <iostream>
using namespace std;

class Shape {
protected:
	double width, height;
	virtual double area() = 0;
public:
	Shape(double w, double h) : width(w), height(h) {}
};

class Triangle : public Shape {
public:
	Triangle(double w, double h) : Shape(w, h) {}
	double area() {
		double a = width * height / 2;
		return a;
	}
};

class Rectangle : public Shape {
public:
	Rectangle(double w, double h) : Shape(w, h) {}
	double area() {
		double a = width * height;
		return a;
	}
};

/*int main() {

	Triangle triangle(5.8, 34.1);
	Rectangle rectangle(5.8, 34.1);

	cout << triangle.area() << '\t' << rectangle.area();

	return 0;
}*/