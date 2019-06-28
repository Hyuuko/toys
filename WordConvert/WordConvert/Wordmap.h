#ifndef _WORDMAP_H
#define _WORDMAP_H


#include "mystring.h"
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

class Wordmap {

  public:
    explicit Wordmap(ifstream& dictionary);

    void output(ifstream& InputFile);
    mystring transword(mystring word); // ??transmap???word

  private:
    map<mystring, mystring> transmap;
};

#endif