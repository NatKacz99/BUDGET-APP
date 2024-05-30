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
int DateMethods::isYearLeap(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return 29;
    }
    else return 28;
}
bool DateMethods::isValidDate(string &date)
{
    if(date.length() != 10)
    {
        cout << "Invalid date format. Try enter again" << endl;
        system("pause");
        return false;
    }
    for (size_t i = 0; i < date.length(); i++)
    {
        if (isdigit(date[0] && date[1] && date[2] && date[3] && date[5] && date[6] && date[8] && date[9]) && date[4] == '-' && date[7] == '-')
        {
            return true;
        }
        else
        {
            cout << "Invalid date format. Try enter again" << endl;
            system("pause");
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
    return true;
}
int DateMethods::convertStringDateToInt(const string &dateAsString)
{
    string dateCopy = dateAsString;
    dateCopy.erase(4,1);
    dateCopy.erase(7,1);
    int dateAsInt = stoi(dateAsString);
    return dateAsInt;
}
string DateMethods::convertIntDateToStringWithDashes(int dateAsInt)
{
    string dateAsString = to_string(dateAsInt);
    dateAsString.insert(4, "-");
    dateAsString.insert(6, "-");
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
    tm now_tm = getCurrentTime();
    now_tm.tm_mday = 0;
    now_tm.tm_mon -= 1;
    if(now_tm.tm_mon == 0){
        now_tm.tm_year -= 1;
        now_tm.tm_mon = 11;
    }

    time_t last_day_c = mktime(&now_tm);
    tm* last_day_tm = localtime(&last_day_c);

    int year = last_day_tm->tm_year + 1900;
    int month = last_day_tm->tm_mon + 1;
    int day = last_day_tm->tm_mday;
    string previousMonthLastDay
    = to_string(year) + '-'
    + (month < 10 ? "0" : "") +
    to_string(month) + '-' +
    (day < 10 ? "0" : "") +
    to_string(day);
    return convertStringDateToInt(previousMonthLastDay);
}
int DateMethods::getPreviousMonthFirstDayDate()
{
    tm now_tm = getCurrentTime();
    now_tm.tm_mday = 1;
    now_tm.tm_mon -= 1;
    if(now_tm.tm_mon == 0){
        now_tm.tm_year -= 1;
        now_tm.tm_mon = 11;
    }

    time_t last_day_c = mktime(&now_tm);
    tm* last_day_tm = localtime(&last_day_c);

    int year = last_day_tm->tm_year + 1900;
    int month = last_day_tm->tm_mon + 1;
    int day = last_day_tm->tm_mday;
    string previousMonthFirstDay
    = to_string(year) + '-'
    + (month < 10 ? "0" : "") +
    to_string(month) + '-' +
    (day < 10 ? "0" : "") +
    to_string(day);
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
