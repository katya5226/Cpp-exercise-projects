template <typename T>
class ImaginaryNumber {
	T x, y;
public:
	ImaginaryNumber() : x(0), y(0) {}
	ImaginaryNumber(T a, T b) : x(a), y(b) {}
	T getReal() const { return x; }
	T getImaginary() const { return y; }

	friend ImaginaryNumber operator +(const ImaginaryNumber& num1, const ImaginaryNumber& num2) {
		T a = num1.getReal() + num2.getReal();
		T b = num1.getImaginary() + num2.getImaginary();
		ImaginaryNumber<T> res(a,b);
		return res;
	}

	/*void operator +=(const ImaginaryNumber& num2) {
		x += num2.getReal();
		y += num2.getImaginary();
	}*/
};
