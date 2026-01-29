//Write a program to calculate how many days from the begining of the year till a given date
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

short DaysInAMonth(short year, short month) {

	if (month < 1 || month > 12) {
		return 0;
	}
	short Days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : Days[month -1];

}


short CalculateDays(short year, short month, short day) {
	short Days = 0;
	for (short i = 1; i < month; i++) {

		Days += DaysInAMonth(year, i);
	}
	Days += day;
	return Days;

}

int main() {
	short Year = ReadNumber("Please enter the year:");
	short Month = ReadNumber("Please enter the month:");
	short Day = ReadNumber("Please enter the day:");

	cout << "There are " << CalculateDays(Year, Month, Day) << " Days passed" << endl;
	return 0;
}