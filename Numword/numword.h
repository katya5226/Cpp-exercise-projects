#pragma once

#ifndef _NUMWORD_H
#define _NUMWORD_H

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cmath>
#include <new>

namespace bw {

	typedef uint64_t nom;
	constexpr nom MY_MAX = 999999999999999999;

	// _maxstr is max size of string
	constexpr size_t _maxstr = 1024;

	static const char* errnum = "error";

    static const char* _singles[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    static const char* _teens[] = {
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };

    static const char* _tens[] = {
        errnum, errnum, "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninty",
    };

    static const char* _hundred = "hundred";

    static const char* _powers[] = {
        errnum, "thousand", "million", "billion", "trillion", "quadrillion"
    };

    static const char* _hyphen = "-";
    static const char* _space = " ";

	class numword {
		nom n = 0;
        char* _buf = nullptr;
        size_t _buflen = 0;
        bool hyphen_flag = false;

        void clearbuf();
        void initbuf();
        void appendspace();
        void appendbuf(const char* s);

	public:
        numword() : n(0) {}
        numword(const nom& num) : n(num) {}
        numword(const numword& b) { n = b.getnum(); };
        ~numword();
        void setnum(const nom& num) { n = num; }
        nom getnum() const { return n; }
        nom operator = (const nom& num);
        const char* words();
        const char* words(const nom& num);
        const char* operator () (const nom& num) { return words(num); }
	};
}

#endif /* _NUMWORD_H */