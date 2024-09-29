#include <iostream>
#include <array>
#include "../../code/nr3.h"
#include "../../code/calendar.h"
#include "../../code/moment.h"
using namespace std;

int main() {
	char myString[] = "A string.";

	char* pMyString = myString;

	cout << pMyString[0] << " " << *pMyString << " " << pMyString[3] << '\n';
	pMyString += 2;
	cout << *pMyString << " " << pMyString[2] << pMyString[5];

	int myArray[5];
	int* pMyArray = myArray;

	cout << "\nEnter 5 integers: ";

	for (int i = 0; i < 5; i++) {
		//cin >> pMyArray[i]; ALI
		cin >> *(pMyArray + i);
	}

	for (const int& i : myArray) {
		cout << '\n' << i;
	}

	for (int i = 4; i >= 0; i--) {
		cout << '\n' << *(pMyArray + i);
	}

	cout << '\n' << "*pMyArray\t" << *pMyArray;
	cout << '\n' << "pMyArray\t" << pMyArray;
	cout << '\n' << "pMyArray[0]\t" << pMyArray[0];
	cout << '\n' << "&pMyArray\t" << &pMyArray;
	cout << '\n' << "*pMyArray + 1\t" << *pMyArray + 1;
	cout << '\n' << "pMyArray + 1\t" << pMyArray + 1;

	
	double x;
	double* p = &x;
	cout << "\n\nEnter a value: ";
	cin >> x;
	cout << "\nYou entered value:\t" << x
		<< "\nThe pointer to that value is p, which is the address of x:\t" << p
		<< "\nOr &x:\t" << &x
		<< "\nThe address of the pointer is &p:\t" << &p
		<< "\nThe value stored where the pointer points is *p:\t" << *p
		<< "\nWhich should be equal to\n" << x;

	const Int NTOT = 20;
	Int i, jd, nph = 2;
	Doub frac, ave, vrnce;
	VecDoub data(NTOT);
	for (i = 0; i < NTOT; i++) {
		flmoon(i, nph, jd, frac);
		data[i] = jd;
	}
	avevar(data, ave, vrnce);
	cout << "Average = " << setw(12) << ave;
	cout << " Variance = " << setw(13) << vrnce << endl;
	

	return 0;
}