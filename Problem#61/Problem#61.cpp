//Write a program to read two periods then count the overlap days if exist

#include <iostream>
#include <string>

using namespace std;

struct stDate {
	short Year, Month, Day;
};

struct stPeriod {
	stDate StartDate, EndDate;
};






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

	return !(IsDate1BeforeDate2(Period2.EndDate, Period1.StartDate) || IsDate1AfterDate2(Period2.StartDate, Period1.EndDate));
}


int CountDays(const stDate& From, const stDate& To) {

	stDate Temp = From;
	int counter = 0;
	while (!IsDate1EqualDate2(Temp, To)) {
		counter++;
		IncreaseDateByOneDay(Temp);
	}
	
	return counter + 1;
}
int ConflictDays(const stPeriod& Period1, const stPeriod& Period2) {
	if (!IsOverlap(Period1, Period2))
		return 0;

	stDate overlapStart = (IsDate1AfterDate2(Period1.StartDate, Period2.StartDate)) ? Period1.StartDate : Period2.StartDate;
	stDate overlapEnd = (IsDate1BeforeDate2(Period1.EndDate, Period2.EndDate)) ? Period1.EndDate : Period2.EndDate;

	return CountDays(overlapStart, overlapEnd);
}
int main() {
	stPeriod Period1 = { {2026,1,5}, {2026,1,10} };
	stPeriod Period2 = { {2026,1,1}, {2026,1,7} };

	int counter = ConflictDays(Period1, Period2);

	cout << (counter == 0 ? "There is no overlap!\n" : to_string(counter));
	return 0;
}