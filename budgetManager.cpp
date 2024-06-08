#include "BudgetManager.h"

void BudgetManager::addExpense()
{
    system("cls");
    cout << "ADDING NEW EXPENSE" << endl;
    Operation expense = addOperationDetails(EXPENSE);
    if(expenseFile.addOperationToFile(expense)){
        expenses.push_back(expense);
        cout << "Expense added right" << endl;
        system("pause");
    }
    else{
        cout << "Problem with adding of expense to file" << endl;
        system("pause");
    }
}
void BudgetManager::addIncome()
{
    system("cls");
    cout << "ADDING NEW INCOME" << endl;
    Operation income = addOperationDetails(INCOME);
    if (incomeFile.addOperationToFile(income)){
        incomes.push_back(income);
        cout << "Income added right" << endl;
        system("pause");
    }
    else{
        cout << "Problem with adding of income to file" << endl;
        system("pause");
    }
}
double BudgetManager::sumIncomesOrExpenses(int startDate, int endDate, const Type &type)
{
    double sum = 0.00;
    switch (type) {
    case INCOME:
        for (size_t i = 0; i < incomes.size(); i++) {
            if (((incomes[i].date) >= startDate) && (incomes[i].date <= endDate)) {
                sum += incomes[i].amount;
            }
        }
        break;
    case EXPENSE:
        for (size_t i = 0; i < expenses.size(); i++) {
            if (((expenses[i].date) >= startDate) && (expenses[i].date <= endDate)) {
                sum += expenses[i].amount;
            }
        }
        break;
    }
    return sum;
}
double BudgetManager::calculateBalance(int startDate, int endDate)
{
    double difference;
    difference = sumIncomesOrExpenses(startDate, endDate, INCOME) - sumIncomesOrExpenses(startDate, endDate, EXPENSE);
    return difference;
}
void BudgetManager::showSingleOperationDetails(Operation &operation)
{
    cout << "Operation ID: " << operation.id << endl;
    cout << "User ID: " << operation.userId << endl;
    cout << "Date: " << operation.date << endl;
    cout << "Item: " << operation.item << endl;
    cout << "Amount: " << operation.amount << endl;
}
Operation BudgetManager::addOperationDetails(const Type &type)
{
    Operation operation;
    string typeDescription, tempDate, tempAmount;
    switch(type)
    {
        case INCOME:
            operation.id = incomeFile.getLastId() + 1;
            typeDescription = "income";
            break;
        case EXPENSE:
            operation.id = expenseFile.getLastId() + 1;
            typeDescription = "expense";
            break;
    }
    operation.userId = LOGGED_USER_ID;
    do{
        cout << "Enter " << typeDescription << " date in YYYY-MM-DD format. Press t to add current date."  << endl;
        tempDate = AuxiliaryMethod::enterLine();
        if(tempDate == "t" || tempDate == "T"){
            tempDate = DateMethods::convertIntDateToStringWithDashes(DateMethods::getCurrentDate());
        }
    }while(!DateMethods::isValidDate(tempDate));
    operation.date = DateMethods::convertStringDateToInt(tempDate);
    cout << "Enter " << typeDescription << " name:" << endl;
    operation.item = AuxiliaryMethod::enterLine();
    do{
        cout << "Enter " << typeDescription << " amount:" << endl;
        tempAmount = AuxiliaryMethod::enterLine();
    }while(!CashMethods::validateAmount(tempAmount));
    operation.amount = stod(tempAmount);

    showSingleOperationDetails(operation);
    return operation;
}
void BudgetManager::showBalance(int startDay, int endDay)
{
    sort(incomes.begin(), incomes.end(), [](const Operation& a, const Operation& b) {
        return a.date < b.date;
    });
    sort(expenses.begin(), expenses.end(), [](const Operation& a, const Operation& b) {
        return a.date < b.date;
    });

    bool hasIncomes = false;
    bool hasExpenses = false;
    if(!(incomes.empty())){
        cout << "Incomes: " << endl;
        for(Operation& income : incomes){
            if(income.date >= startDay && income.date <= endDay)
            {
                showSingleOperationDetails(income);
                hasIncomes = true;
            }
        }
        if(hasIncomes){
            cout << "Incomes sum: " << sumIncomesOrExpenses(startDay, endDay, INCOME) << endl;
        }
        else{
            cout << "Lack of incomes in this period" << endl;
        }
    }
    else cout << "Lack of incomes" << endl;

    if(!(expenses.empty())){
        cout << "Expenses: " << endl;
        for(Operation& expense : expenses){
            if(expense.date >= startDay  && expense.date <= endDay)
            {
                showSingleOperationDetails(expense);
                hasExpenses = true;
            }
        }
        if(hasExpenses){
            cout << "Exspenses sum: " << sumIncomesOrExpenses(startDay, endDay, EXPENSE) << endl;
        }
        else{
            cout << "Lack of expenses in this period" <<  endl;
        }
    }
    else cout << "Lack of expenses" << endl;
    cout << endl;

    if(hasIncomes){
        cout << "Difference betweeen incomes and expenses is: " << calculateBalance(startDay, endDay) << endl;
    }
}
void BudgetManager::showCurrentMonthBalance()
{
    showBalance(DateMethods::getCurrentMonthFirstDayDate(), DateMethods::getCurrentDate());
    system("pause");
}
void BudgetManager::showPreviousMonthBalance()
{
     showBalance(DateMethods::getPreviousMonthFirstDayDate(), DateMethods::getPreviousMonthLastDayDate());
     system("pause");
}
void BudgetManager::showCustomPeriodBalance()
{
    string firstDate, finalDate;
    system("cls");
    cout << "Enter initial date in YYYY-MM-DD format: ";
    do{
        firstDate = AuxiliaryMethod::enterLine();
    }while(!DateMethods::isValidDate(firstDate));
    if(!DateMethods::isValidDate(firstDate)){
        system("pause");
    }
    cout << "Enter final date in YYYY-MM-DD format: ";
    do{
        finalDate = AuxiliaryMethod::enterLine();
    }while(!DateMethods::isValidDate(finalDate));
    if(!DateMethods::isValidDate(finalDate)){
        system("pause");
    }
    showBalance(DateMethods::convertStringDateToInt(firstDate), DateMethods::convertStringDateToInt(finalDate));
    system("pause");
}
