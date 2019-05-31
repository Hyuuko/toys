#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <fstream>
#include <iostream>

using namespace std;

class mystring {
  public:
    mystring() {
        s = NULL;
    }
    mystring(const char* s1);
    mystring(const mystring& s1);
    ~mystring();

    size_t size() {
        return strlen(s);
    }

    mystring mysubstr(int n);

    const mystring& operator=(const mystring& str1);
    bool operator>(const mystring& s1) const;
    bool operator==(const mystring& s1) const;
    bool operator>=(const mystring& s1) const;
    bool operator<(const mystring& s1) const;
    bool operator<=(const mystring& s1) const;
    bool operator!=(const mystring& s1) const;

    char operator[](unsigned i);

    // 不是成员函数
    friend istream& operator>>(istream& sin, mystring& mystr);
    friend ostream& operator<<(ostream& sout, const mystring& mystr);
    friend ifstream& operator>>(ifstream& sin, mystring& mystr);

    friend mystring operator+(const mystring& s1, const mystring& s2);

  private:
    char* s;
};

istream& operator>>(istream& sin, mystring& mystr);
ostream& operator<<(ostream& sout, const mystring& mystr);
ifstream& operator>>(ifstream& sin, mystring& mystr);
mystring operator+(const mystring& s1, const mystring& s2);
#endif