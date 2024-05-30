#include "BudgetAppMain.h"

void BudgetAppMain::addIncome()
{
    if(isUserLoggedIn()){
        budgetManager->addIncome();
    }
    else{
        cout << "You can't add incomes, you aren't logged in" << endl;
    }
}
void BudgetAppMain::addExpense()
{
    if(isUserLoggedIn()){
        budgetManager->addExpense();
    }
    else {
        cout << "You can't add expenses, you aren't logged in" << endl;
    }
}
bool BudgetAppMain::isUserLoggedIn()
{
    return userManager.isUserLoggedIn();
}
void BudgetAppMain::registerUser()
{
    userManager.registerUser();
}
void BudgetAppMain::loginUser()
{
    userManager.loginUser();
    if (isUserLoggedIn()){
        budgetManager = new BudgetManager(INCOME_FILE_NAME, EXPENSE_FILE_NAME, userManager.getLoggedUserId());
    }
}
void BudgetAppMain::showCurrentMonthBalance()
{
    budgetManager->showCurrentMonthBalance();
}
void BudgetAppMain::showPreviousMonthBalance()
{
    budgetManager->showPreviousMonthBalance();
}
void BudgetAppMain::showCustomPeriodBalance()
{
    budgetManager->showCustomPeriodBalance();
}
void BudgetAppMain::showHomeMenu()
{
    system("cls");
    cout << "HOME MENU" << endl;
    cout << "1. Register" << endl;
    cout << "2. Log in" << endl;
    cout << "3. Exit" << endl;
    cout << "Your choice:" << endl;
}
void BudgetAppMain::showLoggedInUserMenu()
{
    cin.sync();
    system("cls");
    cout << "MAIN MENU" << endl;
    cout << "1. Add income" << endl;
    cout << "2. Add expense" << endl;
    cout << "3. Show current month balance" << endl;
    cout << "4. Show previous month balance" << endl;
    cout << "5. Show custom period balance" << endl;
    cout << "6. Replace password" << endl;
    cout << "7. Log off" << endl;

    cout << "Your choice: " << endl;
}
void BudgetAppMain::logOff()
{
    userManager.logoutUser();
    delete budgetManager;
    budgetManager = NULL;
}
void BudgetAppMain::replacePassword()
{
    userManager.changeUserPassword();
}
char BudgetAppMain::getCharacter()
{
   return AuxiliaryMethod::getCharacter();
}
