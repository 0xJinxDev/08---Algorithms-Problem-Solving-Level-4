//Write a program to compare dates

#include <iostream>
#include <string>

using namespace std;

struct stDate
{
	short Year;
	short Month;
	short Day;
};
bool IsDate1BeforeDate2(stDate& Date1, stDate& Date2)
{
	return (Date1.Year < Date2.Year) ? true : ((Date1.Year ==
		Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month ==
			Date2.Month ? Date1.Day < Date2.Day : false)) : false);
}
bool IsDate1EqualDate2(const stDate& Date1, const stDate& Date2)
{
	return Date1.Year == Date2.Year &&
		Date1.Month == Date2.Month &&
		Date1.Day == Date2.Day;
}
bool IsDate1AfterDate2(stDate& Date1, stDate& Date2)
{
	return (!IsDate1BeforeDate2(Date1, Date2) &&
		!IsDate1EqualDate2(Date1, Date2));
}


short ReadNumber(const string& Message) {
	short number;

	do {
		cout << Message << endl;
		cin >> number;
	} while (number <= 0);
	return number;
}

void ReadDate(stDate& Date) {

	Date.Day = ReadNumber("Please enter the day");
	Date.Month = ReadNumber("Please enter the month:");
	Date.Year = ReadNumber("Please enter the year:");
}

enum enDateCompare { Before = -1, Equal = 0, After = 1 };

enDateCompare CompareDates(stDate Date1, stDate Date2)
{
	if (IsDate1BeforeDate2(Date1, Date2))
		return enDateCompare::Before;
	if (IsDate1EqualDate2(Date1, Date2))
		return enDateCompare::Equal;

	return enDateCompare::After;
}

int main() {

	stDate Date1;
	stDate Date2;

	ReadDate(Date1);
	ReadDate(Date2);

	cout << "\nCompare Result = " << CompareDates(Date1, Date2);

	return 0;
}