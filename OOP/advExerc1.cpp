#include <iostream>
using namespace std;

template <typename T>
class imaginaryNum;

//template <typename T>
//imaginaryNum<T> operator +(const imaginaryNum<T> &a);

template <typename T>
class imaginaryNum {
	T x, y;
public:
	imaginaryNum() { x = 0; y = 0; };
	imaginaryNum(T a, T b) : x(a), y(b) {}
	T getReal() const { return x; }
	T getImaginary() const { return y; }
	void setReal(T a) { x = a; }
	void setImaginary(T b) { y = b; }
	//template <typename T>
	//imaginaryNum<T> operator +<>(const imaginaryNum<T>&);
};

template <typename T>
imaginaryNum<T> operator +(const imaginaryNum<T> &a, const imaginaryNum<T> &b) {
	imaginaryNum<T> res;
	T x = a.getReal() + b.getReal();
	T y = a.getImaginary() + b.getImaginary();
	res.setReal(x);
	res.setImaginary(y);
	return res;
}

/*int main() {

	imaginaryNum<double> a(4.1, 8.5);
	imaginaryNum<double> b(2.5, 3.3);
	imaginaryNum<double> c = a + b;

	cout << c.getReal() << " + " << c.getImaginary() << "i";

	return 0;
}*/
