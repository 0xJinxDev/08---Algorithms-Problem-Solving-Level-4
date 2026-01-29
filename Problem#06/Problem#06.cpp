//Write a program to calucalte the number of days, hours , minutes , seconds in a certain month
//Replace the NumberOfDaysInMonth in two lines of code
#include <iostream>
#include <string>

using namespace std;

short ReadNumber(const string& Message) {

    short number;

    do {
        cout << Message << endl;
        cin >> number;
    } while (number <= 0);


    return number;
}

bool IsLeapYear(short year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

short NumberOfDaysInMonth(short month, short year) {
    if (month < 1 || month > 12) {
        return 0;
    }
    return (month == 2) ? (IsLeapYear(year) ? 29 : 28):
        ((month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31);
}
//Below is AbuHadhoud's function
short NumberOfDaysInAMonth(short Month, short Year)
{
    if (Month < 1 || Month>12)
        return 0;
    int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31
    };
    return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) :
        NumberOfDays[Month - 1];
}

short NumberOfHoursInMonth(short month, short year) {

    return NumberOfDaysInMonth(month, year) * 24;
}

int NumberOfMinutesInMonth(short month, short year) {

    return NumberOfHoursInMonth(month, year) * 60;
}
int NumberOfSecondsInMonth(short month, short year) {

    return NumberOfMinutesInMonth(month, year) * 60;
}
int main() {
    short year = ReadNumber("Please enter the year:");
    short month = ReadNumber("Please enter the month:");

    cout << "Number of days in month " << month << " is:" << NumberOfDaysInMonth(month, year) << endl;
    cout << "Number of hours in month " << month << " is:" << NumberOfHoursInMonth(month, year) << endl;
    cout << "Number of minutes in month " << month << " is:" << NumberOfMinutesInMonth(month, year) << endl;
    cout << "Number of seconds in month " << month << " is:" << NumberOfSecondsInMonth(month, year) << endl;
    return 0;
}