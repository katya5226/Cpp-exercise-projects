
#include <iostream>
#include "numword.h"

using namespace std;
using namespace bw;

//max is 10^18

/*void clearbuf();
void initbuf();
void appendspace();
void appendbuf(const char* s);

    public:
        numword() : n(0) {}
        numword(const nom& num) : n(num) {}
        numword(const numword&) {}
        ~numword();
        void setnum(const nom& num) { n = num; }
        nom getnum() const { return n; }
        nom operator = (const nom& num);
        const char* words();
        const char* words(const nom& num);
        const char* operator () (const nom& num) { return words(num); }*/

void numword::clearbuf() {
    if (_buf != nullptr) {
        delete[] _buf;
        _buf = nullptr;
    }
    _buflen = 0;
}

void numword::initbuf() {
    clearbuf();
    try {
        _buf = new char[_maxstr];
        *_buf = 0;
        hyphen_flag = false;
    }
    catch (bad_alloc e) {
        printf("numword: cannot allocate buffer: %s\n", e.what());
    }
}

void numword::appendspace() {
    if (_buflen) {
        appendbuf(hyphen_flag ? _hyphen : _space);
        hyphen_flag = false;
    }
}

void numword::appendbuf(const char * s) {
    if (!s) return;
    size_t slen = strnlen(s, _maxstr);
    if (slen < 1) return;
    if ((slen + _buflen + 1) >= _maxstr) return;
    memcpy(_buf + _buflen, s, slen);
    _buflen += slen;
    _buf[_buflen] = 0;
}

numword::~numword() {
    clearbuf();
}

nom numword::operator = (const nom& num) {
    setnum(num);
    return getnum();
}

const char* numword::words() {
    return words(n);
};

const char* numword::words(const nom& num) {
    if (num > MY_MAX) return errnum;

    initbuf();
    nom number = num;
    if (number == 0) {
        appendbuf(_singles[number]);
        return _buf;
    }

    // powers of 1000
    if (number >= 1000) {
        for (int i = 5; i > 0; --i) {
            nom power = (nom)pow(1000.0, i);
            nom _n = (number - (number % power)) / power;
            if (_n) {
                int index = i;
                numword _nw(_n);
                appendspace();
                appendbuf(_nw.words());
                appendspace();
                appendbuf(_powers[index]);
                number -= _n * power;
            }
        }
    }
    // hundreds
    if (number >= 100 && number < 1000) {
        nom _n = (number - (number % 100)) / 100;
        numword _nw(_n);
        appendspace();
        appendbuf(_nw.words());
        appendspace();
        appendbuf(_hundred);
        number -= _n * 100;
    }
    // tens
    if (number >= 20 && number < 100) {
        nom _n = (number - (number % 10)) / 10;
        appendspace();
        appendbuf(_tens[_n]);
        number -= _n * 10;
        hyphen_flag = true;
    }
    // teens
    if (number >= 10 && number < 20) {
        appendspace();
        appendbuf(_teens[number - 10]);
        number = 0;
    }
    // singles
    if (number > 0 && number < 10) {
        appendspace();
        appendbuf(_singles[number]);
    }
    return _buf;
};