//Write a program to tell the number of Days, hours , minutes , seconds in a certain year
#include <iostream>
#include <string>


using namespace std;

short ReadNumber(const string& Message) {
	short number;
	do {
		cout << Message << endl;
		cin >>number;
	} while (number <= 0);
	return number;
}


bool IsLeapYear(short year) {

	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);


}

short NumberOfDays(short year) {
	return IsLeapYear(year) ? 366 : 365;
}

short NumberOfHours(short year) {

	return NumberOfDays(year) * 24;
}

int NumberOfMinutes(short year) {

	return NumberOfHours(year) * 60;
}

int NumberOfSeconds(int year) {

	return NumberOfMinutes(year) * 60;
}

int main() {
	while (1) {
		short year = ReadNumber("Please enter the year:");
		
		cout << "Number of days: " << NumberOfDays(year)<<endl;
		cout << "Number of hours: " << NumberOfHours(year) << endl;
		cout << "Number of minutes: " << NumberOfMinutes(year) << endl;
		cout << "Number of seconds: " << NumberOfSeconds(year) << endl;

	}


	return 0;
}