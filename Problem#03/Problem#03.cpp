//Write a program to check if a year is leap or not with one line of code

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

bool IsLeapYear(short number) {

	return (number % 400 == 0) || (number % 4 == 0 && number % 100 != 0);
}

int main() {

	short year = ReadNumber("Please enter the year:");

	cout << (IsLeapYear(year) ? "Leap year.\n" : "Not a leap year.\n");
	return 0;
}