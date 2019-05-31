#include "mystring.h"
#include <cstring>

#pragma warning(disable : 4996)

mystring::mystring(const char* s1) {
    if (s1) {
        s = new char[strlen(s1) + 1];
        strcpy(s, s1);
    } else
        s = NULL;
}

mystring::mystring(const mystring& s1) {
    if (s1.s) {
        s = new char[strlen(s1.s) + 1];
        strcpy(s, s1.s);
    } else
        s = NULL;
}

// 析构
mystring::~mystring() {
    if (s)
        delete[] s;
}

mystring mystring::mysubstr(int n) {

    mystring newmystr;
    auto len   = strlen(this->s);
    newmystr.s = new char[len + 1];
    for (int i = 0; i != len - n; i++) {
        s[i] = s[i + n];
    }

    return newmystr;
}

const mystring& mystring::operator=(const mystring& s1) {
    if (this != &s1) {
        if (s)
            delete[] s;
        s = new char[strlen(s1.s) + 1];
        strcpy(s, s1.s);
    }
    return *this;
}

// 流提取
istream& operator>>(istream& sin, mystring& mystr) {
    char c[256];
    sin >> c;
    mystr = mystring(c);
    return sin;
}

// 流插入
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

// 比较 >
bool mystring::operator>(const mystring& s1) const {
    for (int i = 0;; ++i) {
        if (this->s[i] != s1.s[i])
            return this->s[i] > s1.s[i];
        else if (!this->s[i] && !s1.s[i])
            return false;
    }
}

// 比较 ==
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
    // 第一步不能用strcat，strcat要求连接前的两个字符串后面都有'\0'
    strcpy(s.s, s1.s);
    strcat(s.s, s2.s);
    return s;
}
