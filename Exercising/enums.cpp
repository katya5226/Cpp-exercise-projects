#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>


enum class parts { chex, diodeA, mcm, diodeB, hhex };


void printSomething(parts a) {
	
}

/*class myClass {
public:
	const std::vector<double>& makeVector() const;
};

const std::vector<double>& myClass::makeVector() const {
	const std::vector<double> aVec{ 4,6,5,8 };
	return aVec;
}*/

void changeVector(std::vector<std::vector<double>>& vec) {
	vec[0].push_back(0.2);
}

//int main() {
//
//	int diodeA = 2;
//	
//	double b = 6.60;
//	double* pb = &b;
//	
//
//	std::cout << 2 * (*pb) * 1 << std::endl;
//	
//	std::vector<std::vector<double>> vec;
//	std::vector<double> element;
//	vec.push_back(element); 
//	changeVector(vec);
//
//	std::cout << vec[0][0];
//
//	//const std::vector<double>& myVec = C.makeVector();
//
//	//std::cout << myVec[0];
//
//	double a = 596.493847562;
//	double f = 333.482763940;
//	double c = 0.00000462222;
//	double i = 77.394985111;
//	double e = 0.77744444111;
//	double g = 5.6666662222;
//
//	double d = a + f*c + i/e - g;
//
//	std::cout << std::setprecision(15) << "\n rezultat je : " << d << std::endl;
//
//	std::vector<double> myVec{ 1,2,3,4,5,6,7,8,9,10 };
//	std::vector<double> copiedVec(myVec);
//	myVec.erase(myVec.begin());
//	myVec.erase(myVec.end()-1);
//
//	copiedVec = myVec;
//	myVec.erase(myVec.begin());
//	copiedVec = myVec;
//	int N = copiedVec.size();
//	for (int i = 0; i < N; i++) {
//		std::cout << copiedVec[i] << "  ";
//	}
//	std::cout << '\n';
//	for (int i = 0; i < myVec.size(); i++) {
//		std::cout << myVec[i] << "  ";
//	}
//
//	return 0;
//}
