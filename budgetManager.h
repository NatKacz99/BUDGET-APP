#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "itemType.h"
#include "Markup.h"
#include "Operation.h"
#include "dateMethods.h"
#include "filesOperation.h"
#include "auxiliaryMethod.h"
#include "cashMethods.h"
using namespace std;

class BudgetManager
{
    FilesOperation incomeFile;
    FilesOperation expenseFile;
    const int LOGGED_USER_ID;
    vector <Operation> incomes;
    vector <Operation> expenses;
    double calculateBalance(int startDate, int endDate);
    double sumIncomesOrExpenses(int startDate, int endDate, const Type &type);
    Operation addOperationDetails(const Type &type);
    void showBalance(int startDay, int endDay);
public:
    BudgetManager(string incomeFileName, string expenseFileName, int loggedUserId) : incomeFile(incomeFileName), expenseFile(expenseFileName), LOGGED_USER_ID(loggedUserId) {
        incomes = incomeFile.loadOperationsFromFile(LOGGED_USER_ID);
        expenses = expenseFile.loadOperationsFromFile(LOGGED_USER_ID);
    }
    void addExpense();
    void addIncome();
    void showCurrentMonthBalance();
    void showPreviousMonthBalance();
    void showCustomPeriodBalance();
    void showSingleOperationDetails(Operation &operation);
};

#endif
