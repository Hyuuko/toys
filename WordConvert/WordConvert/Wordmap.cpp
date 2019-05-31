#include "Wordmap.h"
#include <cassert>

Wordmap::Wordmap(ifstream& dictionary) {
    assert(dictionary);

    mystring key, value;
    while (dictionary >> key >> value) {
        transmap[key] = value;
    }
}

void Wordmap::output(ifstream& InputFile) {
    mystring text;
    bool firstword = true;
    while (InputFile >> text) {
        if (firstword)
            firstword = false;
        else
            cout << " ";
        cout << transword(text);
    }
}

mystring Wordmap::transword(mystring word) {
    auto map_it = transmap.find(word);
    if (map_it != transmap.cend()) // if find it
        return map_it->second;     // return the value
    else
        return word; // if not found, return the word
    // TODO: 在此处插入 return 语句
}
