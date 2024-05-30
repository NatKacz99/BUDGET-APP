#ifndef FILESOPERATION_H
#define FILESOPERATION_H

#include <iostream>
#include <vector>
#include "Markup.h"
#include "File.h"
#include "Operation.h"

using namespace std;

class FilesOperation : public File
{
    CMarkup xml;
public:
    FilesOperation (string fileName) : File(fileName) {}
    vector <Operation> loadOperationsFromFile (const int loggedUserId);
    bool addOperationToFile (const Operation &operation);
};

#endif
