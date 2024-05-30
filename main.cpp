#include <iostream>
#include <cstdlib>
#include "BudgetAppMain.h"
#include "auxiliaryMethod.h"

using namespace std;

int main()
{
    BudgetAppMain budgetAppMain("incomes.xml", "expenses.xml", "users.xml");
    char choice;

    while(1){
        if(!budgetAppMain.isUserLoggedIn()){
            budgetAppMain.showHomeMenu();
            choice = budgetAppMain.getCharacter();
            switch(choice)
            {
            case '1':
                budgetAppMain.registerUser();
                break;
            case '2':
                budgetAppMain.loginUser();
                break;
            case '3':
                exit(0);
                break;
            default:
                cout << "Character not used. Try again" << endl;
                system("pause");
                break;
            }
        }
        else{
            budgetAppMain.showLoggedInUserMenu();
            choice = budgetAppMain.getCharacter();
            switch(choice)
            {
            case '1':
                budgetAppMain.addIncome();
                break;
            case '2':
                budgetAppMain.addExpense();
                break;
            case '3':
                budgetAppMain.showCurrentMonthBalance();
                break;
            case '4':
                budgetAppMain.showPreviousMonthBalance();
                break;
            case '5':
                budgetAppMain.showCustomPeriodBalance();
                break;
            case '6':
                budgetAppMain.replacePassword();
                break;
            case '7':
                budgetAppMain.logOff();
                break;
            default:
                cout << "Characted not used. Try again" << endl;
                break;
            }
        }
    }
    return 0;
}
