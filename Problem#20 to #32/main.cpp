//Write the following functions:
//IncreaseDateByOneDay -- Done
//IncreaseDateByXDays -- Done
//IncreaseDateByOneWeek -- Done
//IncreaseDateByXWeeks -- Done
//IncreaseDateByOneMonth
//IncreaseDateByXMonth
//IncreaseDateByOneYear
//IncreaseDateByXYears
//IncreaseDateByXYearsFaster
//IncreaseDateByOneDecade
//IncreaseDateByXDecades
//IncreaseDateByXDecadesFaster
//IncreaseDateByOneCentury
//IncreaseDateByOneMillennium

#include<iostream>
#include<string>

using namespace std;

struct stDate {

	short Year, Month, Day;

};

short ReadNubmer(const string& Message) {
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
	short Months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	return Date.Month == 2 ? IsLeapYear(Date.Year) ? 29 : 28 : Months[Date.Month - 1];
}

bool IsLastDayInTheMonth(const stDate& Date) {
	return Date.Day == DaysInAMonth(Date);
}
bool IsLastDayInTheYear(const stDate& Date) {
	return Date.Month == 12 && IsLastDayInTheMonth(Date);
}

void IncreaseDateByOneDay(stDate& Date) {

	if (IsLastDayInTheYear(Date)) {
		Date.Year++;
		Date.Month = 1;
		Date.Day = 1;
	}
	else if (IsLastDayInTheMonth(Date)) {
		Date.Month++;
		Date.Day = 1;
	}
	else {
		Date.Day++;
	}
}

void IncreaseDateByXDays(stDate& Date, int DaysToIncrease) {

	for (int i = 0; i < DaysToIncrease; i++) {
		IncreaseDateByOneDay(Date);
	}

}
void IncreaseDateByOneWeek(stDate& Date) {
	IncreaseDateByXDays(Date, 7);
}

void IncreaseDateByXWeeks(stDate& Date, int WeeksToIncrease) {

	IncreaseDateByXDays(Date, WeeksToIncrease * 7);
}

void IncreaseDateByOneMonth(stDate& Date) {
	
	if (Date.Month == 12) {
		Date.Year++;
		Date.Month = 1;
	}
	else{
		Date.Month++;
		if (Date.Day > DaysInAMonth(Date)) {
			Date.Day = DaysInAMonth(Date);
		}
	}


}
string PrintDate(const stDate& Date) {



	return to_string(Date.Day)+"/"+to_string(Date.Month)+"/"+to_string(Date.Year);

}

int main() {

	stDate Date;
	Date.Year = 2025;
	Date.Month = 1;
	Date.Day = 1;
	string line;

	IncreaseDateByOneDay(Date);
	cout << "Date after increasing one day: " << PrintDate(Date) << endl;
	IncreaseDateByXDays(Date, 15);
	cout << "Date after increasing 15 day: " << PrintDate(Date) << endl;
	IncreaseDateByOneWeek(Date);
	cout << "Date after increasing one week: " << PrintDate(Date) << endl;
	IncreaseDateByXWeeks(Date, 3);
	cout << "Date after increasing 3 weeks: " << PrintDate(Date) << endl;

	return 0;
}