//Write the following functions:
//IncreaseDateByOneDay -- Done
//IncreaseDateByXDays -- Done
//IncreaseDateByOneWeek -- Done
//IncreaseDateByXWeeks -- Done
//IncreaseDateByOneMonth -- Done
//IncreaseDateByXMonth -- Done
//IncreaseDateByOneYear -- Done
//IncreaseDateByXYears -- Done
//IncreaseDateByXYearsFaster -- Done
//IncreaseDateByOneDecade -- Done
//IncreaseDateByXDecades -- Done
//IncreaseDateByXDecadesFaster -- Done
//IncreaseDateByOneCentury -- Done
//IncreaseDateByOneMillennium -- Done


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

void IncreaseDateByXMonths(stDate& Date, int MonthsToIncrease) {

	for (int i = 0; i < MonthsToIncrease; i++) {

		IncreaseDateByOneMonth(Date);
	}
}


void IncreaseDateByOneYear(stDate& Date) {

	Date.Year++;
	if (Date.Month == 2 && Date.Day > DaysInAMonth(Date)) {
		Date.Day = DaysInAMonth(Date);
	}
	
}

void IncreaseDateByXYears(stDate& Date, int YearsToIncrease) {

	for (short i = 0; i < YearsToIncrease; i++) {
		IncreaseDateByOneYear(Date);
	}

}

void IncreaseDateByXYearsFaster(stDate& Date, int YearsToIncrease) {
	Date.Year += YearsToIncrease;
	if (Date.Month == 2 && Date.Day > DaysInAMonth(Date)) {
		Date.Day = DaysInAMonth(Date);
	}
}

void IncreaseDateByOneDecade(stDate& Date) {

	IncreaseDateByXYearsFaster(Date, 10);

}

void IncreaseDateByXDecades(stDate& Date, int DecadesToIncrease) {

	for (int i = 0; i < DecadesToIncrease; i++) {
		IncreaseDateByOneDecade(Date);
	}

}

void IncreaseDateByXDecadesFaster(stDate& Date, int DecadesToIncrease) {

	Date.Year += DecadesToIncrease * 10;
	if (Date.Month == 2 && Date.Day > DaysInAMonth(Date)) {
		Date.Day = DaysInAMonth(Date);
	}
}


void IncreaseDateByOneCentury(stDate& Date) {
	IncreaseDateByXDecadesFaster(Date, 10);
}

void IncreaseDateByOneMillennium(stDate& Date) {

	IncreaseDateByXDecadesFaster(Date, 100);
}

string PrintDate(const stDate& Date) {

	return to_string(Date.Day)+"/"+to_string(Date.Month)+"/"+to_string(Date.Year);

}


int main() {

	stDate Date;
	Date.Year = 2019;
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
	IncreaseDateByOneMonth(Date);
	cout << "Date after increasing one month: " << PrintDate(Date) << endl;
	IncreaseDateByXMonths(Date, 2);
	cout << "Date after increasing 2 months: " << PrintDate(Date) << endl;
	IncreaseDateByOneYear(Date);
	cout << "Date after increasing one year: " << PrintDate(Date) << endl;
	IncreaseDateByXYears(Date, 2);
	cout << "Date after increasing two years: " << PrintDate(Date) << endl;
	IncreaseDateByXYearsFaster(Date, 2);
	cout << "Date after increasing two years (faster): " << PrintDate(Date) << endl;
	IncreaseDateByOneDecade(Date);
	cout << "Date after increasing one decade: " << PrintDate(Date) << endl;
	IncreaseDateByXDecades(Date, 2);
	cout << "Date after increasing two decades: " << PrintDate(Date) << endl;
	IncreaseDateByXDecadesFaster(Date, 2);
	cout << "Date after increasing two decades (faster): " << PrintDate(Date) << endl;
	IncreaseDateByOneCentury(Date);
	cout << "Date after increasing one century: " << PrintDate(Date) << endl;
	IncreaseDateByOneMillennium(Date);
	cout << "Date after increasing one millenium: " << PrintDate(Date) << endl;


	return 0;
}