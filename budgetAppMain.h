#ifndef BUDGETAPPMAIN_H
#define BUDGETAPPMAIN_H

#include <iostream>
#include <cstdlib>
#include "BudgetManager.h"
#include "UserManager.h"
using namespace std;

class BudgetAppMain
{
    const string INCOME_FILE_NAME;
    const string EXPENSE_FILE_NAME;
    BudgetManager *budgetManager;
    UserManager userManager;
public:
    BudgetAppMain(string incomeFileName, string expenseFileName, string userFileName) : INCOME_FILE_NAME(incomeFileName), EXPENSE_FILE_NAME(expenseFileName), userManager(userFileName){
        budgetManager = NULL;
    };
    ~BudgetAppMain()
    {
        delete budgetManager;
        budgetManager = NULL;
    }
    bool isUserLoggedIn();
    void registerUser();
    void showCurrentMonthBalance();
    void showSelectedPeriodBalance();
    void showPreviousMonthBalance();
    void showCustomPeriodBalance();
    void logOff();
    void showHomeMenu();
    void loginUser();
    void showLoggedInUserMenu();
    void addIncome();
    void addExpense();
    void replacePassword();
    char getCharacter();
};
#endif
