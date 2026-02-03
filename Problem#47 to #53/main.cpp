//Write a program to do the following
// CalculateDayOrder to take sructure
// IsEndOfWeek
// IsWeekEnd
// IsBusinessDay
// DaysUntilTheEndOfWeek
// DaysUntilTheEndOfMonth
// DaysUntilTheEndOfYear

#pragma warning(disable : 4996)
#include<iostream>
#include<string>

using namespace std;

struct stDate {
	short Year, Month, Day;
};
bool IsLeapYear(const int Year) {
	return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
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

short CalculateDayOrder(const stDate & Date) {

	int a = (14 - Date.Month) / 12;
	int y = Date.Year - a;
	int m = Date.Month + (12 * a) - 2;

	short d = (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	return d;
}
short DaysInAMonth(const stDate& Date) {

	if (Date.Month < 1 || Date.Month > 12) {
		return 0;
	}
	short Months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return Date.Month == 2 ? IsLeapYear(Date.Year) ? 29 : 28 : Months[Date.Month - 1];
}
string ReadDate(const stDate& Date) {
	return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
}
string GetDayName(const stDate& Date) {

	short order = CalculateDayOrder(Date);

	switch (order) {
	case 0: return "Sun";
	case 1: return "Mon";
	case 2: return "Tue";
	case 3: return "Wed";
	case 4: return "Thu";
	case 5: return "Fri";
	case 6: return "Sat";
	}
}

bool IsEndOfWeek(const stDate& Date) {
	return CalculateDayOrder(Date) == 6;
}
bool IsWeekEnd(const stDate& Date) {
	short order = CalculateDayOrder(Date);
	return order == 5 || order == 6;
}
bool IsBusinessDay(const stDate& Date) {
	return (!IsWeekEnd(Date));
}

short DaysUntilTheEndOfWeek(const stDate& Date) {

	return 6 - CalculateDayOrder(Date);
}

short DaysUntilTheEndOfMonth(const stDate& Date) {
	return DaysInAMonth(Date) - Date.Day;
}
short DaysSinceTheBeginingOfYear(const stDate& Date) {
	
	short counter = 0;
	short CurrentMonth = Date.Month;
	for (short i = 1; i < Date.Month; i++) {
		counter += DaysInAMonth({ Date.Year, i, 1 });
	}

	counter += Date.Day;
	return counter;
}
short DaysUntilTheEndOfYear(const stDate& Date) {
	short DaysPassed = DaysSinceTheBeginingOfYear(Date);
	return IsLeapYear(Date.Year) ? 366 - DaysPassed : 365 - DaysPassed;
}
int main() {

	stDate DateNow = GetSystemDate();
	string Date;

	cout << "Today is " << GetDayName(DateNow) << " " << ReadDate(DateNow)<< endl <<endl;
	cout << "Is it end of the week?\n";
	cout << (IsEndOfWeek(DateNow) ? "Yes.\n" : "No.\n");
	cout << "Is it weekend ?\n";
	cout << (IsWeekEnd(DateNow) ? "Yes.\n" : "No.\n");
	cout << "Is it business day?\n";
	cout << (IsBusinessDay(DateNow) ? "Yes.\n" : "No.\n");

	cout << "Days until the end of week: " << DaysUntilTheEndOfWeek(DateNow) << endl;
	cout << "Days until the end of month: " << DaysUntilTheEndOfMonth(DateNow) << endl;
	cout << "Days until the end of year: " << DaysUntilTheEndOfYear(DateNow) << endl;
	
	return 0;
}