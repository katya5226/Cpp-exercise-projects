/*#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;

class BadLengthException : public runtime_error
{
public:
	BadLengthException(int length) : runtime_error{ to_string(length) }
	{ }
};


bool checkUsername(string username) {
	bool isValid = true;
	int n = username.length();
	if (n < 5) {
		throw BadLengthException(n);
	}
	for (int i = 0; i < n - 1; i++) {
		if (username[i] == 'w' && username[i + 1] == 'w') {
			isValid = false;
		}
	}
	return isValid;
}

int main() {

	string username = "Ty";
	try {
		bool isValid = checkUsername(username);
		if (isValid) {
			cout << "Valid" << '\n';
		}
		else {
			cout << "Invalid" << '\n';
		}
	}
	catch (BadLengthException e) {
		cout << "Too short: " << e.what() << '\n';
	}

	//string s = to_string(2);
	//char const* pchar = s.c_str();
	//cout << *pchar;

	return 0;
}*/