#include "stringbuffer.h"

void ms::sentence::clearbuf() {
	if (buf != nullptr) {
		delete[] buf;
		buf = nullptr;
	}
}

void ms::sentence::initbuf() {
	clearbuf();
	try {
		buf = new char[maxstr];
		*buf = 0;
	}
	catch (std::bad_alloc e) {
		printf("%s\n", e.what());
	}
}

ms::sentence::sentence() {
	initbuf();
}


void ms::sentence::appendbuf(const char* s) {
	int slen = strlen(s);
	memcpy(buf + buflen, s, slen);
	buflen += slen;
	buf[buflen] = 0;
}

const char* ms::sentence::makeSentence(const int arr[], const int &n) {
	initbuf();
	for (int i = 0; i < n; i++) {
		int m = arr[i];
		appendbuf(words[m]);
		appendbuf(" ");
	}
	return buf;
}