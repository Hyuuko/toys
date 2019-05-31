#pragma once
#include "mystring.h"
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Wordmap {

  public:
    explicit Wordmap(ifstream &dictionary);

    void output(ifstream& InputFile);
    mystring transword(mystring word); //  π”√transmap¿¥∑≠“Îword

  private:
    map<mystring, mystring> transmap;
};
