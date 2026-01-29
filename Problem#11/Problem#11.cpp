//Write a program to calculate how many days from the begining of the year till a given date
//Then take the days and convert them back into a date
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
	return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : Days[month - 1];

}


short CalculateDays(short year, short month, short day) {
	short Days = 0;
	for (short i = 1; i < month; i++) {

		Days += DaysInAMonth(year, i);
	}
	Days += day;
	return Days;

}

string NumberOfDaysToYear(short year, short NumberOfDays) {

	short month = 1;

	while (NumberOfDays > DaysInAMonth(year, month)) {
		NumberOfDays -= DaysInAMonth(year, month);
		month++;
	}

	short day = NumberOfDays;

	return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}

int main() {
	short Year = 2026;
	short Month = 1;
	short Day = 29;
	short NumberOfDays = CalculateDays(Year, Month, Day);

	cout << "Number of days from the begining of the year is " << NumberOfDays << endl;

	string s = NumberOfDaysToYear(Year, NumberOfDays);
	cout << s;
	return 0;
}