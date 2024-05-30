#ifndef AUXILIARYMETHOD_H
#define AUXILIARYMETHOD_H

#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdlib>

using namespace std;

class AuxiliaryMethod
{
public:
    static bool validateInput(string input);
    static char getCharacter();
    static string enterLine();
};

#endif
