#pragma once
#include <cstring>

class animal {
	const char * name;
public:
	void setname(const char * s) { name = s; }
	const char * getname() { return name; }
};