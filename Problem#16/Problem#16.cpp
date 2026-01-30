//Write a program to increase a date with one day



#include <iostream>
#include <string>


using namespace std;


struct stDate {

	short Year, Month, Day;

};

short ReadNumber(const string& Message) {
	short number;

	do {

		cout << Message << endl;
		cin >> number;

	} while (number <= 0);
	return number;
}
void ReadDate(stDate& Date) {
	Date.Year = ReadNumber("Please enter the year:");
	Date.Month = ReadNumber("Please enter the month:");
	Date.Day = ReadNumber("Please enter the day:");

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
bool IsLastDayInAMonth(const stDate& Date) {

	return (Date.Day == DaysInAMonth(Date.Year, Date.Month));
}
bool IsLastDayInAYear(const stDate& Date) {
	return (Date.Month == 12 && IsLastDayInAMonth(Date));
}

void IncreaseDay(stDate& Date) {

	if (IsLastDayInAYear(Date)) {
		Date.Year++;
		Date.Month = 1;
		Date.Day = 1;
	}
	else if (IsLastDayInAMonth(Date)) {
		Date.Month++;
		Date.Day = 1;
	}
	else {
		Date.Day++;
	}
}
int main() {

	stDate Date;

	ReadDate(Date);
	IncreaseDay(Date);

	cout << Date.Day << endl;
	cout << Date.Month << endl;
	cout << Date.Year << endl;

}
