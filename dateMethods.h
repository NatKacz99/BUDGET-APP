#ifndef DATEMETHODS_H
#define DATEMETHODS_H

#include <iostream>
#include <map>
#include <time.h>
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>
#include <regex>
using namespace std;

class DateMethods{
static void calculateCurrentDate(map<string, int> &currentDate);
static int isYearLeap(int year);
public:
static tm getCurrentTime();
static bool isValidDate(string &date);
static int convertStringDateToInt(const string &dateAsString);
static string convertIntDateToStringWithDashes(int dateAsInt);
static int getCurrentMonthFirstDayDate();
static int getPreviousMonthLastDayDate();
static int getPreviousMonthFirstDayDate();
static int getCurrentDate();
};

#endif
