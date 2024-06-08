#ifndef CASHMETHODS_H
#define CASHMETHODS_H

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;

class CashMethods
{
public:
    static bool validateAmount(string &amount);
    static string formatAmount(double &amount);
};

#endif
