/*#include <iostream>
#include <string>

class Rectangle {
private:
	int width{0};
	int height{0};
public:
	Rectangle() {}

	Rectangle(int x, int y) {
		width = x;
		height = y;
	}

	int area() {
		return width * height;
	}
	friend Rectangle duplicate(const Rectangle&);
};

Rectangle duplicate(const Rectangle& param) {
	Rectangle res;
	res.width = param.width * 2;
	res.height = param.height * 2;
	return res;
}

int main() {
	Rectangle doubled;
	Rectangle rectangle = Rectangle(10, 20);
	doubled = duplicate(rectangle);
	std::cout << doubled.area();

	return 0;
}*/