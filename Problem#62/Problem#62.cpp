//Write a program to read a date then validate this date


#include <iostream>
#include <string>

using namespace std;

short ReadNumber(const string& Message) {
	short number;
	cout << Message << endl;
	cin >> number;
	return number;
}

struct stDate {
	short Year, Month, Day;
};

void ReadDate(stDate& Date) {
	Date.Day = ReadNumber("Please enter the day:");
	Date.Month = ReadNumber("Please enter the month");
	Date.Year = ReadNumber("Please enter the year:");

}
bool IsLeapYear(const stDate& Date) {
	return (Date.Year % 400 == 0) || (Date.Year % 4 == 0 && Date.Year % 100 != 0);
}
short DaysInAMonth(const stDate& Date) {
	if (Date.Month < 1 || Date.Month >12 || Date.Year <= 0) {
		return 0;
	}
	short Months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (Date.Month == 2) ? IsLeapYear(Date) ? 29 : 28 : Months[Date.Month - 1];
}

bool IsValidDate(const stDate& Date) {
    short days = DaysInAMonth(Date);
    return (days != 0 && Date.Day >= 1 && Date.Day <= days);
}
int main() {
	stDate Date;
	ReadDate(Date);

	cout << (IsValidDate(Date) ? "Yes, it's a valid date.\n" : "No, it's not a valid date.\n");

}