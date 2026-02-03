#include <iostream>
#include <string>

using namespace std;

struct stDate {
	short Year, Month, Day;
};

short ReadNumber(const string& Message) {

	short number;

	do {
		cout << Message << endl;
		cin >> number;
	} while (number <= 0);

	return number;
}

bool IsLeapYear(short year) {
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

short DaysInAMonth(const stDate& Date) {

	if (Date.Month < 1 || Date.Month > 12) {
		return 0;
	}
	short Months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return Date.Month == 2 ? IsLeapYear(Date.Year) ? 29 : 28 : Months[Date.Month - 1];
}

bool IsLastDayInAMonth(const stDate& Date) {

	return Date.Day == DaysInAMonth(Date);

}

bool IsLastDayInTheYear(const stDate& Date) {

	return Date.Month == 12 && IsLastDayInAMonth(Date);
}

bool IsFirstDayInAMonth(const stDate& Date) {
	return Date.Day == 1;
}

void DecreaseDateByOneDay(stDate& Date) {

	if (Date.Month == 1 && IsFirstDayInAMonth(Date)) {
		Date.Year--;
		Date.Month = 12;
		Date.Day = 31;
	}
	else if (IsFirstDayInAMonth(Date)) {
		Date.Month--;
		Date.Day = DaysInAMonth(Date);
	}
	else {
		Date.Day--;
	}

}

void DecreaseDateByXDays(stDate& Date, int DaysToDecrease) {

	for (int i = 0; i < DaysToDecrease; i++) {
		DecreaseDateByOneDay(Date);
	}

}

void DecreaseDateByOneWeek(stDate& Date) {

	DecreaseDateByXDays(Date, 7);
}

void DecreaseDateByXWeeks(stDate& Date, int WeeksToDecrease) {
	DecreaseDateByXDays(Date, WeeksToDecrease * 7);
}

void DecreaseDateByOneMonth(stDate& Date) {

	if (Date.Month == 1) {
		Date.Year--;
		Date.Month = 12;
	}
	else {
		Date.Month--;
		if (Date.Day > DaysInAMonth(Date)) {
			Date.Day = DaysInAMonth(Date);
		}
	}
}

void DecreaseDateByXMonths(stDate& Date, int MonthsToDecrease) {

	for (int i = 0; i < MonthsToDecrease; i++) {
		DecreaseDateByOneMonth(Date);
	}
}

void DecreaseDateByOneYear(stDate& Date) {
	Date.Year--;

	if (Date.Day > DaysInAMonth(Date)) {
		Date.Day = DaysInAMonth(Date);
	}
}

void DecreaseDateByXYears(stDate& Date, int YearsToDecrease) {

	for (int i = 0; i < YearsToDecrease; i++) {

		DecreaseDateByOneYear(Date);
	}
}

void DecreaseDateByXYearsFaster(stDate& Date, int YearsToDecrease) {
	Date.Year -= YearsToDecrease;

	if (Date.Day > DaysInAMonth(Date)) {
		Date.Day = DaysInAMonth(Date);
	}

}


void DecreaseDateByOneDecade(stDate& Date) {
	DecreaseDateByXYearsFaster(Date, 10);
}

void DecreaseDateByXDecades(stDate& Date, int DecadesToDecrease) {
	DecreaseDateByXYearsFaster(Date, DecadesToDecrease * 10);
}

void DecreaseDateByXDecadesFaster(stDate& Date, int DecadesToDecrease) {
	Date.Year -= DecadesToDecrease * 10;

	if (Date.Day > DaysInAMonth(Date)) {
		Date.Day = DaysInAMonth(Date);
	}
}

void DecreaseDateByOneCentury(stDate& Date) {
	DecreaseDateByXYearsFaster(Date, 100);
}

void DecreaseDateByOneMillennium(stDate& Date) {
	DecreaseDateByXYearsFaster(Date, 1000);
}


string PrintDate(const stDate& Date) {

	return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);

}


int main() {
	stDate Date;
	Date.Year = 2026;
	Date.Month = 1;
	Date.Day = 1;
	string line;

	DecreaseDateByOneDay(Date);
	cout << "Date after decreasing one day: " << PrintDate(Date) << endl;
	DecreaseDateByXDays(Date, 10);
	cout << "Date after decreasing 10 days: " << PrintDate(Date) << endl;
	DecreaseDateByOneWeek(Date);
	cout << "Date after decreasing one week: " << PrintDate(Date) << endl;
	DecreaseDateByXWeeks(Date, 2);
	cout << "Date after decreasing 2 weeks: " << PrintDate(Date) << endl;
	DecreaseDateByOneMonth(Date);
	cout << "Date after decreasing one month: " << PrintDate(Date) << endl;
	DecreaseDateByXMonths(Date, 2);
	cout << "Date after decreasing 2 months: " << PrintDate(Date) << endl;
	DecreaseDateByOneYear(Date);
	cout << "Date after decreasing one year: " << PrintDate(Date) << endl;
	DecreaseDateByXYears(Date, 2);
	cout << "Date after decreasing 2 years: " << PrintDate(Date) << endl;
	DecreaseDateByXYearsFaster(Date, 2);
	cout << "Date after decreasing 2 years (faster): " << PrintDate(Date) << endl;
	DecreaseDateByOneDecade(Date);
	cout << "Date after decreasing one decade: " << PrintDate(Date) << endl;
	DecreaseDateByXDecades(Date, 3);
	cout << "Date after decreasing 3 decades: " << PrintDate(Date) << endl;
	DecreaseDateByXDecadesFaster(Date, 5);
	cout << "Date after decreasing 5 decades (faster): " << PrintDate(Date) << endl;
	DecreaseDateByOneCentury(Date);
	cout << "Date after decreasing one century: " << PrintDate(Date) << endl;
	DecreaseDateByOneMillennium(Date);
	cout << "Date after decreasing one millennium: " << PrintDate(Date) << endl;

	return 0;
}
