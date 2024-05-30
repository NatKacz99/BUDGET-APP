#include "cashMethods.h"

bool CashMethods::validateAmount(string amount)
{
    size_t commaPosition = amount.find(',');
    if(commaPosition != string:: npos){
        replace(amount.begin(), amount.end(), ',', '.');
        return true;
    }
    return false;
}
