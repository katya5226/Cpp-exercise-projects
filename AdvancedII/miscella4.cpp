#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;


string remove_letter_easy(string str, char c)
{
	str.erase(std::remove(str.begin(), str.end(), c), str.end());
	return str;
}

string remove_letter(string str, char c)
{
	for (auto iter = str.begin(); iter != str.end(); )
	{
		if (*iter == c) iter = str.erase(iter);
		else ++iter;
	}
	return str;
}


int main() {

	char aString[] = "Hobotnica";
	char aChar = 'o';
	int occurence = 0;

	char* pch = aString;
	//cout << (void*)pch << endl;
	int iterr = 0;

	while (iterr<=8) {
		if (*pch == aChar) {
			pch++;
		}
		else {
			//cout << *pch;
			pch++;
		}
		iterr++;
	}
	cout << endl;
	string myString = "octopus";
	
	cout << remove_letter(myString, aChar) <<endl;
	cout << remove_letter_easy(myString, aChar) << endl;


	return 0;
}