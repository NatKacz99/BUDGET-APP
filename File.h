#ifndef FILE_H
#define FILE_H

#include <iostream>
#include "Markup.h"
using namespace std;

class File
{
    const string FILE_NAME;
protected:
    int lastId;
    CMarkup xml;
    File(string fileName) : FILE_NAME(fileName){
        lastId = 0;
    }
    const string getFileName();
public:
    int getLastId();
};

#endif
