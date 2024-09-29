#include "stringbuffer.h"


int main() {

	ms::sentence mySentence;

	const int n = 5;
	const int arr[n] = { 3, 6, 4, 8, 6 };

	const char* p = mySentence.makeSentence(arr, 5);

	printf("%s\n", p);

	return 0;
}





