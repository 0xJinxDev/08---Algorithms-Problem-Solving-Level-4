//Write a program to calculate the different between 2 dates and support if date 2 is less than date 1

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

bool IsLeapYear(const short Year) {
	return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
}

void ReadDate(stDate& Date) {
	Date.Year = ReadNumber("Please enter the year");
	Date.Month = ReadNumber("Please enter the month");
	Date.Day = ReadNumber("Please enter the day");
}

short DaysInAMonth(short year, short month) {

	if (month < 1 || month > 12) {
		return 0;
	}
	short Days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : Days[month - 1];

}

short DaysTillAGivenDate(const stDate& Date) {
	short counter = 0;
	for (short i = 1; i < Date.Month; i++) {
		counter += DaysInAMonth(Date.Year, i);

	}
	counter += Date.Day;
	return counter;
}

short CalculateDifferance(const stDate& Date1, const stDate& Date2) {
	short Differance = 0;

	if (Date1.Year == Date2.Year) {
		Differance = DaysTillAGivenDate(Date2) - DaysTillAGivenDate(Date1);
	}
	else if (Date1.Year < Date2.Year) {

		for (short i = Date1.Year + 1; i < Date2.Year; i++) {
			Differance += IsLeapYear(i) ? 366 : 365;
		}

		Differance += IsLeapYear(Date1.Year)
			? 366 - DaysTillAGivenDate(Date1)
			: 365 - DaysTillAGivenDate(Date1);

		Differance += DaysTillAGivenDate(Date2);
	}
	else {

		for (short i = Date2.Year + 1; i < Date1.Year; i++) {
			Differance += IsLeapYear(i) ? 366 : 365;
		}

		Differance += IsLeapYear(Date2.Year)
			? 366 - DaysTillAGivenDate(Date2)
			: 365 - DaysTillAGivenDate(Date2);

		Differance += DaysTillAGivenDate(Date1);

		Differance *= -1;
	}

	return Differance;
}


int main() {

	stDate Date1, Date2;
	ReadDate(Date1);
	ReadDate(Date2);

	short diff = CalculateDifferance(Date1, Date2);

	cout << "The differrance is: " << diff << " days.\n";
	return 0;
}