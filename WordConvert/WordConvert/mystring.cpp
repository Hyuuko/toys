#include "mystring.h"
#include <cassert>
#pragma warning(disable : 4996)

char* mystrcpy(char* strDest, const char* strSrc);
char* mystrcpy(char* strDest, const char* strSrc) {
    assert((strDest != NULL) && (strSrc != NULL));
    char* address = strDest;
    while ((*strDest++ = *strSrc++) != '\0')
        ;
    return address;
}

mystring::mystring(const char* s1) {
    if (s1) {
        s = new char[strlen(s1) + 1];
        mystrcpy(s, s1);
    } else
        s = NULL;
}

mystring::mystring(const mystring& s1) {
    if (s1.s) {
        s = new char[strlen(s1.s) + 1];
        mystrcpy(s, s1.s);
    } else
        s = NULL;
}

// ����
mystring::~mystring() {
    if (s)
        delete[] s;
}

mystring mystring::mysubstr(unsigned n) {

    mystring newmystr;
    auto len   = strlen(this->s);
    newmystr.s = new char[len + 1];
    for (unsigned i = 0; i != len - n; i++) {
        s[i] = s[i + n];
    }

    return newmystr;
}

const mystring& mystring::operator=(const mystring& s1) {
    if (this != &s1) {
        if (s)
            delete[] s;
        s = new char[strlen(s1.s) + 1];
        mystrcpy(s, s1.s);
    }
    return *this;
}

// ����ȡ
istream& operator>>(istream& sin, mystring& mystr) {
    char c[256];
    sin >> c;
    mystr = mystring(c);
    return sin;
}

// ������
ostream& operator<<(ostream& sout, const mystring& mystr) {
    sout << mystr.s;
    return sout;
}

ifstream& operator>>(ifstream& sin, mystring& mystr) {

    char c[256];
    sin >> c;
    mystr = mystring(c);
    return sin;
}

// �Ƚ� >
bool mystring::operator>(const mystring& s1) const {
    for (int i = 0;; ++i) {
        if (this->s[i] != s1.s[i])
            return this->s[i] > s1.s[i];
        else if (!this->s[i] && !s1.s[i])
            return false;
    }
}

// �Ƚ� ==
bool mystring::operator==(const mystring& s1) const {
    for (int i = 0;; ++i) {
        if (this->s[i] != s1.s[i])
            return false;
        else if (!this->s[i] && !s1.s[i])
            return true;
    }
}

bool mystring::operator>=(const mystring& s1) const {
    return (*this > s1 || *this == s1);
}
bool mystring::operator<(const mystring& s1) const {
    return !(*this > s1) && !(*this == s1);
}
bool mystring::operator<=(const mystring& s1) const {
    return !(*this > s1);
}
bool mystring::operator!=(const mystring& s1) const {
    return !(*this == s1);
}

char mystring::operator[](unsigned i) {
    return this->s[i];
}

mystring operator+(const mystring& s1, const mystring& s2) {
    mystring s;
    s.s = new char[strlen(s1.s) + strlen(s2.s) + 1];
    mystrcpy(s.s, s1.s);
    mystrcpy(s.s + s.size(), s2.s);
    return s;
}
