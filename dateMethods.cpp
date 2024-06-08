#include "DateMethods.h"

tm DateMethods::getCurrentTime()
{
    auto currentTime = chrono::system_clock::now();
    time_t currentDateTime = chrono::system_clock::to_time_t(currentTime);
    tm now_tm = *localtime(&currentDateTime);
    return now_tm;
}
void DateMethods::calculateCurrentDate(map<string, int> &currentDate)
{
    tm currentTm = getCurrentTime();

    currentDate["year"] = currentTm.tm_year + 1900;
    currentDate["month"] = currentTm.tm_mon + 1;
    currentDate["day"] = currentTm.tm_mday;
}
bool DateMethods::isYearLeap(string &year){
    if ((stoi(year) % 4 == 0 && stoi(year) % 100 != 0) || (stoi(year) % 400 == 0)){
        return true;
    }
    else{
        return false;
    }
}
int DateMethods::returnNumberOfDaysInMonth(string year, string month)
{
    map <int,int> daysOfMonths;

    daysOfMonths[1] = 31;
    daysOfMonths[3] = 31;
    daysOfMonths[4] = 30;
    daysOfMonths[5] = 31;
    daysOfMonths[6] = 30;
    daysOfMonths[7] = 31;
    daysOfMonths[8] = 31;
    daysOfMonths[9] = 30;
    daysOfMonths[10] = 31;
    daysOfMonths[11] = 30;
    daysOfMonths[12] = 31;

    if (isYearLeap(year) == true){
        daysOfMonths[2] = 29;
    }
    else{
        daysOfMonths[2] = 28;
    }

    return daysOfMonths[stoi(month)];
}
bool DateMethods::isValidDate(string &date)
{
    if (date.length() != 10){
        cout << "Invalid date format. Please enter the date in format with 10 symbols." << endl;
        return false;
    }

    for (int i = 0; i < 10; ++i){
        if ((i == 4 || i == 7) && date[i] != '-'){
            cout << "Invalid date format. Please enter the date in YYYY-MM-DD format." << endl;
            return false;
        }
        else if (i != 4 && i != 7 && !isdigit(date[i])){
            cout << "Invalid date format. Please enter the date in YYYY-MM-DD format." << endl;
            return false;
        }
    }

    map <string, int> currentDate;
    stringstream ss;

    calculateCurrentDate(currentDate);

    if (date == "T" || date == "t"){
        ss << currentDate["year"] <<  "-" << (currentDate["month"] < 10 ? "0" : "") << currentDate["month"] << "-" << (currentDate["day"] < 10 ? "0" : "") << currentDate["day"];
        date = ss.str();
        return true;
    }

    if (!regex_match(date, regex("[0-9]{4}-[0-9]{2}-[0-9]{2}"))){
        cout << "Incorrect date format. Try again" << endl;
        return false;
    }

    string year = date.substr(0, 4);
    string month = date.substr(5, 2);
    string day = date.substr(8, 2);

    if (stoi(month) < 1 || stoi(month) > 12) {
        cout << "Invalid month. Please enter a month between 01 and 12." << endl;
        return false;
    }

    int daysInMonth = returnNumberOfDaysInMonth(year, month);
    if (stoi(day) < 1 || stoi(day) > daysInMonth) {
        cout << "Invalid day. Please enter a valid day for the given month." << endl;
        return false;
    }

    int inputDate = convertStringDateToInt(date);
    if (stoi(year) < 2000 || inputDate > getCurrentDate()) {
        cout << "Date doesn't fit in the correct period. Enter a date between 2000-01-01 and the current date." << endl;
        return false;
    }
    return true;
}
int DateMethods::convertStringDateToInt(const string &dateAsString)
{
    string dateCopy = dateAsString;
    dateCopy.erase(4,1);
    dateCopy.erase(6,1);
    int dateAsInt = stoi(dateCopy);
    return dateAsInt;
}
string DateMethods::convertIntDateToStringWithDashes(int dateAsInt)
{
    string dateAsString = to_string(dateAsInt);
    dateAsString.insert(4, "-");
    dateAsString.insert(7, "-");
    return dateAsString;
}
int DateMethods::getCurrentMonthFirstDayDate()
{
    tm now_tm = getCurrentTime();
    now_tm.tm_mday = 1;
    time_t first_day_c = mktime(&now_tm);
    tm* first_day_tm = localtime(&first_day_c);
    int year = first_day_tm->tm_year + 1900;
    int month = first_day_tm->tm_mon + 1;
    int day = first_day_tm->tm_mday;
    string currentMonthFirstDayDate
    = to_string(year) + '-' +
    (month < 10 ? "0" : "") +
    to_string(month) + '-' +
    (day < 10 ? "0" : "") +
    to_string(day);
    return convertStringDateToInt(currentMonthFirstDayDate);
}
int DateMethods::getPreviousMonthLastDayDate()
{
    stringstream ss(convertIntDateToStringWithDashes(getCurrentDate()));
    string phrase, month;
    int year, monthAmount, day;

    getline(ss, phrase, '-');
    year = stoi(phrase);
    getline(ss, phrase, '-');
    month = phrase;
    monthAmount = stoi(month);

    if (monthAmount == 1) {
        year -= 1;
        monthAmount = 12;
    } else {
        monthAmount -= 1;
    }

    day = returnNumberOfDaysInMonth(to_string(year), to_string(monthAmount));

    string previousMonthLastDay = to_string(year) + '-' +
                                  (monthAmount < 10 ? "0" : "") + to_string(monthAmount) + '-' +
                                  (day < 10 ? "0" : "") + to_string(day);

    return convertStringDateToInt(previousMonthLastDay);
}
int DateMethods::getPreviousMonthFirstDayDate()
{
    stringstream ss(convertIntDateToStringWithDashes(getCurrentDate()));
    string phrase, month;
    int year, monthAmount;

    getline(ss, phrase, '-');
    year = stoi(phrase);
    getline(ss, phrase, '-');
    month = phrase;
    monthAmount = stoi(month);

    if (monthAmount == 1) {
        year -= 1;
        monthAmount = 12;
    } else {
        monthAmount -= 1;
    }

    string previousMonthFirstDay = to_string(year) + '-' +
                                   (monthAmount < 10 ? "0" : "") + to_string(monthAmount) + '-' +
                                   "01";
    return convertStringDateToInt(previousMonthFirstDay);
}
int DateMethods::getCurrentDate()
{
    map<string, int> currentDate;
    calculateCurrentDate(currentDate);
    stringstream ss;
    ss << currentDate["year"] << '-'
       << setw(2) << setfill('0') << currentDate["month"] << '-'
       << setw(2) << setfill('0') << currentDate["day"];
    return convertStringDateToInt(ss.str());
}
