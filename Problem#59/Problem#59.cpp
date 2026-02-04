//Write a program to read a period then calculate the periods in days
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

void ReadDate(stDate& Date) {
	Date.Day = ReadNumber("Please enter the day");
	Date.Month = ReadNumber("Please enter the month");
	Date.Year = ReadNumber("Please enter the year");
}

void ReadPeriod(stPeriod& Period) {
	cout << "Please enter start date:\n";
	ReadDate(Period.StartDate);
	cout << "Please enter end date:\n";
	ReadDate(Period.EndDate);

}
bool IsLeapYear(const stDate& Date) {

	return (Date.Year % 400 == 0) || (Date.Year % 4 == 0 && Date.Year % 100 != 0);

}

short DaysInAMonth(const stDate& Date) {
	if (Date.Month < 1 || Date.Month >12) {
		return 0;
	}
	short Months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (Date.Month == 2) ? IsLeapYear(Date) ? 29 : 28 : Months[Date.Month - 1];
}

bool IsLastDayInAMonth(const stDate& Date) {
	return Date.Day == DaysInAMonth(Date);
}
bool IsLastDayInAYear(const stDate& Date) {
	return Date.Month == 12 && IsLastDayInAMonth(Date);
}
void IncreaseDateByOneDay(stDate& Date) {

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
int CountPeriodDays(const stPeriod& Period) {

	stDate temp = Period.StartDate;
	int counter = 0;
	while (!IsDate1EqualDate2(temp, Period.EndDate)) {
		IncreaseDateByOneDay(temp);
		counter++;

	}
	return counter + 1;
}
int main() {
	stPeriod Period;
	ReadPeriod(Period);
	
	cout << "Number of days in this period:" << CountPeriodDays(Period);
	return 0;
}