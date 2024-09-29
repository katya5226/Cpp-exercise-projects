#include <iostream>
#include <memory>
#include <locale>
#include <algorithm>
#include "lambdas.h"

int main() {

	animal A;
	A.setname("Piggy");
	const char* name = A.getname();
	//std::shared_ptr<std::string> pName = std::make_shared<std::string>(name);

	puts(name);

	char lastc = 0;
	char s[] = "This is my new code";
	std::transform(s, s + strlen(s), s, [&lastc](const char& c) -> char {
		const char r = (lastc == ' ' || lastc == 0) ? toupper(c) : tolower(c);
		lastc = c;
		return r;
	});

	puts(s);

	return 0;
}