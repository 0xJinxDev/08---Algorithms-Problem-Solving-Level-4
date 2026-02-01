//Write a program to calculate your age

#pragma warning(disable : 4996)
#include <iostream>
#include <string>

using namespace std;

int ReadNumber(const string& Message) {

	int number;

	do {
		cout << Message << endl;
		cin >> number;
	} while (number <= 0);

	return number;

}

struct stDate {

	int Year, Month, Day;
};

bool IsLeapYear(const int Year) {
	return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
}

void ReadDate(stDate& Date) {
	Date.Year = ReadNumber("Please enter the year");
	Date.Month = ReadNumber("Please enter the month");
	Date.Day = ReadNumber("Please enter the day");
}

int DaysInAMonth(int year, int month) {

	if (month < 1 || month > 12) {
		return 0;
	}
	int Days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : Days[month - 1];

}

int DaysTillAGivenDate(const stDate& Date) {
	int counter = 0;
	for (int i = 1; i < Date.Month; i++) {
		counter += DaysInAMonth(Date.Year, i);

	}
	counter += Date.Day;
	return counter;
}

int CalculateDifferance(const stDate& Date1, const stDate& Date2) {
	int Differance = 0;
	if (Date1.Year == Date2.Year) {

		Differance = DaysTillAGivenDate(Date2) - DaysTillAGivenDate(Date1);
	}

	if (Date1.Year < Date2.Year) {

		for (int i = Date1.Year + 1; i < Date2.Year; i++) {
			Differance += IsLeapYear(i) ? 366 : 365;
		}
		Differance += IsLeapYear(Date1.Year) ? 366 - DaysTillAGivenDate(Date1) : 365 - DaysTillAGivenDate(Date1);
		Differance += DaysTillAGivenDate(Date2);
	}
	return Differance;
}
stDate GetSystemDate()
{
	stDate Date;
	time_t t = time(0);
	tm* now = localtime(&t);
	Date.Year = now->tm_year + 1900;
	Date.Month = now->tm_mon + 1;
	Date.Day = now->tm_mday;
	return Date;
}

int main() {

	stDate Date1,Date2 = GetSystemDate();
	ReadDate(Date1);

	int diff = CalculateDifferance(Date1, Date2);

	cout << "Your age is: "<< diff << " days.\n";
	return 0;
}