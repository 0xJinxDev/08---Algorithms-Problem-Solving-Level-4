//Write a program to check if a date within a period or not

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

struct stDate {
	short Year, Month, Day;
};

struct stPeriod {
	stDate StartDate, EndDate;
};

void ReadDate(stDate& Date) {
	Date.Day = ReadNumber("Please enter the day:");
	Date.Month = ReadNumber("Please enter the month:");
	Date.Year = ReadNumber("Please enter the year:");

}

void ReadPeriod(stPeriod& Period) {
	cout << "Please enter start date:" << endl;
	ReadDate(Period.StartDate);
	cout << "Please enter end date:" << endl;
	ReadDate(Period.EndDate);
}


bool IsDate1BeforeDate2(const stDate& Date1, const stDate& Date2)
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
bool IsDate1AfterDate2(const stDate& Date1, const stDate& Date2)
{
	return (!IsDate1BeforeDate2(Date1, Date2) &&
		!IsDate1EqualDate2(Date1, Date2));
}

bool IsWithinPeriod(const stDate& Date, const stPeriod& Period) {

	return !(IsDate1BeforeDate2(Date, Period.StartDate) || IsDate1AfterDate2(Date,Period.EndDate));

}

int main() {


	stPeriod Period;
	stDate Date;
	ReadPeriod(Period);
	ReadDate(Date);

	cout << (IsWithinPeriod(Date, Period) ? "The date is within the period.\n" : "The date is not within the period.\n");


	return 0;
}