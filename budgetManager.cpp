#include "BudgetManager.h"

void BudgetManager::addExpense()
{
    system("cls");
    cout << "ADDING NEW EXPENSE" << endl;
    Operation expense = addOperationDetails(EXPENSE);
    expenses.push_back(expense);
    expenseFile.addOperationToFile(expense);
    if(expenseFile.addOperationToFile(expense)){
        cout << "Expense added right" << endl;
    }
    else{
        cout << "Problem with adding of expense to file" << endl;
    }
}
void BudgetManager::addIncome()
{
    system("cls");
    cout << "ADDING NEW INCOME" << endl;
    Operation income = addOperationDetails(INCOME);
    incomes.push_back(income);
    incomeFile.addOperationToFile(income);
    if (incomeFile.addOperationToFile(income)){
        cout << "Income added right" << endl;
    }
    else{
        cout << "Problem with adding of income to file" << endl;
    }
}
double BudgetManager::sumIncomesOrExpenses(int startDate, int endDate, const Type &type)
{
    double sum = 0.00;
    switch (type) {
    case INCOME:
        for (size_t i = 0; i < incomes.size(); i++) {
            if ((DateMethods::convertStringDateToInt(incomes[i].date) >= startDate) && (DateMethods::convertStringDateToInt(incomes[i].date) <= endDate)) {
                sum += incomes[i].amount;
            }
        }
        break;
    case EXPENSE:
        for (size_t i = 0; i < expenses.size(); i++) {
            if ((DateMethods::convertStringDateToInt(expenses[i].date) >= startDate) && (DateMethods::convertStringDateToInt(expenses[i].date) <= endDate)) {
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
void BudgetManager::showSingleOperationDetails(Operation operation)
{
    cout << operation.id << endl;
    cout << operation.userId << endl;
    cout << operation.date << endl;
    cout << operation.item << endl;
    cout << operation.amount << endl;
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
        case EXPENSE:
            operation.id = expenseFile.getLastId() + 1;
            typeDescription = "expense";
    }
    operation.userId = LOGGED_USER_ID;

    do{
        cout << "Enter " << typeDescription << " date. Press t to add current date."  << endl;
        tempDate = AuxiliaryMethod::enterLine();
    }while(!DateMethods::isValidDate(tempDate));

    operation.date = DateMethods::convertStringDateToInt(tempDate);

    cout << "Enter " << typeDescription << " name:" << endl;
    operation.item = AuxiliaryMethod::enterLine();

    do{
        cout << "Enter " << typeDescription << " amount." << endl;
        tempAmount = AuxiliaryMethod::enterLine();
    }while(!CashMethods::validateAmount(tempAmount));

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

    if(!(incomes.empty())){
        for(Operation income : incomes){
            showSingleOperationDetails(income);
        }
        cout << "Incomes sum: " << sumIncomesOrExpenses(startDay, endDay, INCOME) << endl;
    }
    else cout << "Lack of incomes" << endl;

    if(!(expenses.empty())){
       for(Operation expense : expenses){
            showSingleOperationDetails(expense);
       }
       cout << "Exspenses sum: " << sumIncomesOrExpenses(startDay, endDay, EXPENSE) << endl;
    }
    else cout << "Lack of expenses" << endl;

    cout << "Difference betweeen incomes and expenses is: " << calculateBalance(startDay, endDay) << endl;
}
void BudgetManager::showCurrentMonthBalance()
{
    showBalance(DateMethods::getCurrentMonthFirstDayDate(), DateMethods::getCurrentDate());
}
void BudgetManager::showPreviousMonthBalance()
{
     showBalance(DateMethods::getPreviousMonthFirstDayDate(), DateMethods::getPreviousMonthLastDayDate());
}
void BudgetManager::showCustomPeriodBalance()
{
    string firstDate, finalDate;
    system("cls");
    cout << "Enter initial date in YYYY-MM-DD format: ";
     firstDate = AuxiliaryMethod::enterLine();
    if(!DateMethods::isValidDate(firstDate)){
        cout << "Date is in incorrect format. Try again" << endl;
        system("pause");
    }
    cout << "Enter final date in YYYY-MM-DD format: ";
    finalDate = AuxiliaryMethod::enterLine();
    if(!DateMethods::isValidDate(finalDate)){
        cout << "Date is in incorrect format. Try again" << endl;
        system("pause");
    }
    showBalance(DateMethods::convertStringDateToInt(firstDate), DateMethods::convertStringDateToInt(finalDate));
}
