//Write a program to read date, then ask the user to input how many days he wants to add, then print the new date after addition

#include <iostream>
#include <string>

using namespace std;


short ReadNumber(const string& Message) {
	short number;
	do{
		cout << Message << endl;
		cin >> number;
	} while (number <= 0);

	return number;
}


bool IsLeapYear(short year) {
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

short DaysInAMonth(short year, short month) {

	if (month < 1 || month > 12) {
		return 0;
	}
	short Days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : Days[month - 1];

}



string AddDays(short& year, short& month, short& day, short days) {

	while (days > 0) {

		short DaysInCurrentMonth = DaysInAMonth(year, month);

		if (day + days <= DaysInCurrentMonth) {
			day += days;
			days = 0;
		}
		else {
			days -= (DaysInCurrentMonth - day + 1);
			day = 1;
			month++;

			if (month > 12) {
				month = 1;
				year++;
			}
		}
	}

	return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}


int main() {

	short Year = ReadNumber("Please enter the year:");
	short Month = ReadNumber("Please enter the month:");
	short Day = ReadNumber("Please enter the day:");
	
	short DaysToAdd = ReadNumber("Please enter how many days to add?");

	string NewDate = AddDays(Year, Month, Day, DaysToAdd);

	cout << NewDate << endl;

	return 0;
}