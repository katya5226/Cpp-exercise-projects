#include <iostream>
#include <string>
using namespace std;

class Mother {
protected:
	const string name;
	const int age;
public:
	Mother(const string mName, const int mAge) : name(mName), age(mAge) {}
	void display() {
		cout << "The mother's name is " << name
			<< " and her age is " << age << "." << endl;
	}
};

class Daughter : public Mother {
public:
	Daughter(const string dName, const int dAge) : Mother(dName, dAge) {}
	void display() {
		cout << "The daughter's name is " << name
			<< " and her age is " << age << "." << endl;
	}
};

/*int main() {

	Mother minci("Minci", 33);
	Daughter lili("Lili", 8);

	minci.display();
	lili.display();

	return 0;
}*/