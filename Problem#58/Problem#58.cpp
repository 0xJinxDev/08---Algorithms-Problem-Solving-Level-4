//Write a program to enter two periods and check if they overlap or not

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


bool IsOverlap(const stPeriod& Period1, const stPeriod& Period2) {


	return !(IsDate1AfterDate2(Period2.StartDate, Period1.EndDate) ||
		IsDate1BeforeDate2(Period2.EndDate, Period1.StartDate));

}
int main() {

	
	stPeriod Period1, Period2;
	cout << "Please enter period 1:" << endl;
	ReadPeriod(Period1);
	cout << "Please enter period 2:" << endl;
	ReadPeriod(Period2);
	
	cout << (IsOverlap(Period1, Period2) ? "There is overlap.\n" : "There is no overlap.\n");


	return 0;
}