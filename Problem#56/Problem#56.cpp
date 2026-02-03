// Write a program to check if date 1 after date 2
#include <iostream>
#include <string>

using namespace std;

struct stDate
{
	short Year;
	short Month;
	short Day;
};
bool IsDate1BeforeDate2(stDate & Date1, stDate & Date2)
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
bool IsDate1AfterDate2(stDate & Date1, stDate & Date2)
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


int main() {

	stDate Date1;
	stDate Date2;

	ReadDate(Date1);
	ReadDate(Date2);

	cout << (IsDate1AfterDate2(Date1, Date2) ? "Yes.\n" : "No.\n");


	return 0;
}