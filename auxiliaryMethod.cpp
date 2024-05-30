#include "auxiliaryMethod.h"

bool AuxiliaryMethod::validateInput(string input)
{
    return input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- ") == string::npos;
}
char AuxiliaryMethod::getCharacter()
{
    string input = "";
    char character = {0};
    while(true){
        getline(cin, input);

        if (input.length() == 1){
            character = input[0];
            break;
        }
        else{
            cout << "It isn't a single character. Try again" << endl;
            system("pause");
        }
    }
    return character;
}
string AuxiliaryMethod::enterLine()
{
    string input = "";
    getline(cin, input);
    return input;
}

