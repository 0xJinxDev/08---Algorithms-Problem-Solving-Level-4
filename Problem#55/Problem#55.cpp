//Write a program to receive a date then ask the user of how many days he wants as a vacation
//then calculate the new date

#include<iostream>
#include<string>
using namespace std;

struct stDate {
	short Year, Month, Day;
};
bool IsLeapYear(const int Year) {
	return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
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
short CalculateDayOrder(const stDate& Date) {

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
string PrintDate(const stDate& Date) {
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


bool IsWeekEnd(const stDate& Date) {
	short order = CalculateDayOrder(Date);
	return order == 5 || order == 6;
}
bool IsBusinessDay(const stDate& Date) {
	return (!IsWeekEnd(Date));
}


bool IsLastDayInMonth(const stDate& Date) {
	return Date.Day == DaysInAMonth(Date);
}
bool IsLastDayInYear(const stDate& Date) {
	return Date.Month == 12 && IsLastDayInMonth(Date);
}

void IncreaseDateByDay(stDate& Date) {

	if (IsLastDayInYear(Date)) {
		Date.Year++;
		Date.Month = 1;
		Date.Day = 1;
	}
	else if (IsLastDayInMonth(Date)) {
		Date.Month++;
		Date.Day = 1;
	}
	else {
		Date.Day++;
	}



}
stDate CalculateBalance(const stDate& StartDate, short Days) {
	stDate EndDate = StartDate;

	while (Days > 0) {
		
		if (IsBusinessDay(EndDate)) {
			Days--;
		}

		if (Days >0)
		IncreaseDateByDay(EndDate);
	}
	
	while (IsWeekEnd(EndDate)) {
		IncreaseDateByDay(EndDate);
	}
	return EndDate;

}
int main() {

	stDate StartDate, EndDate;
	cout << "Please enter the start date:\n";
	ReadDate(StartDate);
	short Days = ReadNumber("Please enter how many days you want:");
	EndDate = CalculateBalance(StartDate, Days);

	cout << "Start date " << GetDayName(StartDate) << " " << PrintDate(StartDate) << endl;
	cout << "End date " << GetDayName(EndDate) << " " << PrintDate(EndDate) << endl;

	return 0;
}