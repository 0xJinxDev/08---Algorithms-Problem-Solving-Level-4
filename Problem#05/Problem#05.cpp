//Write a program to calucalte the number of days, hours , minutes , seconds in a certain month
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

    if (month == 2) {
        return IsLeapYear(year) ? 29 : 28;
    }

    short arr31Days[7] = { 1, 3, 5, 7, 8, 10, 12 };
    for (short i = 0; i < 7; i++) {
        if (arr31Days[i] == month) {
            return 31;
        }
    }

    return 30;
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

    cout << "Number of days in month " << month <<" is:" << NumberOfDaysInMonth(month, year)<< endl;
    cout << "Number of hours in month " << month << " is:" << NumberOfHoursInMonth(month, year) << endl;
    cout << "Number of minutes in month " << month << " is:" << NumberOfMinutesInMonth(month, year) << endl;
    cout << "Number of seconds in month " << month << " is:" << NumberOfSecondsInMonth(month, year) << endl;
    return 0;
}