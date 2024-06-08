#include "cashMethods.h"

bool CashMethods::validateAmount(string &amount)
{
    if (amount.empty()) {
        cout << "Empty value. Try again" << endl;
        system("pause");
        return false;
    }

    for (char symbol : amount) {
        if (!isdigit(symbol) && symbol != '.' && symbol != ',') {
            cout << "Entered amount contains incorrect symbols. Try enter again." << endl;
            system("pause");
            return false;
        }
    }

    size_t commaPosition = amount.find(',');
    if (commaPosition != string::npos)
    {
        replace(amount.begin(), amount.end(), ',', '.');
    }
    return true;
}
string CashMethods::formatAmount(double &amount) {
    ostringstream oss;
    oss << fixed << setprecision(2) << amount;
    return oss.str();
}
