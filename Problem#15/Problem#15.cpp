//Write a program to check if this is the last day in the month and if its the last day in the year

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

	return (Date.Day == DaysInAMonth(Date.Year,Date.Month));
}
bool IsLastDayInAYear(const stDate& Date) {
	return (Date.Month == 12 && IsLastDayInAMonth(Date));
}
int main() {

	stDate Date;

	ReadDate(Date);
	
	cout << (IsLastDayInAMonth(Date) ? "Last day in the month\n" : "Not last day in the month\n");
	cout << (IsLastDayInAYear(Date) ? "Last day in the year\n" : "Not last day in the year\n");
	

}