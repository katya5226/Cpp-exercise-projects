#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
	string name;
	int age;
public:
	virtual void setValue(string aName, int anAge) {
		name = aName;
		age = anAge;
	}
};

class Zebra : public Animal {
public:
	void setValue(string aName, int anAge) {
		name = aName;
		age = anAge;
		cout << name << ", " << age << ", from Africa." << endl;
	}
};

class Dolphin : public Animal {
public:
	void setValue(string aName, int anAge) {
		name = aName;
		age = anAge;
		cout << name << ", " << age << ", from the ocean." << endl;
	}
};

/*int main() {

	Zebra zebra;
	Dolphin dolphin;

	Animal* ptr1 = &zebra;
	Animal* ptr2 = &dolphin;

	ptr1 -> setValue("Mimi", 3);
	ptr2 -> setValue("Oli", 7);
	
	return 0;
}*/