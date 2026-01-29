//Write a program to read a date then print the day's name and its order of in the week

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
void DateToString(string& Date, short day, short month, short year) {
	Date.clear();
	Date += to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}

short CalculateDayOrder(short year, short month, short day) {

	int a = (14 - month) / 12;
	int y = year - a;
	int m = month + (12 * a) - 2;

	short d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	return d;
}
string DetermineDay(short DayOrder) {

	switch (DayOrder) {

	case 0:
		return "Sunday";
	case 1:
		return "Monday";
	case 2:
		return "Tuesday";
	case 3:
		return "Wednesday";
	case 4:
		return "Thursday";
	case 5:
		return "Friday";
	case 6:
		return "Saturday";
	default:
		return "Invalid Day";
	}
}
int main() {

	short Year = ReadNumber("Please enter the year:");
	short Month = ReadNumber("Please enter the month");
	short Day = ReadNumber("Please enter the day:");
	string Date;
	DateToString(Date, Day, Month, Year);
	short DayOrder = CalculateDayOrder(Year, Month, Day);
	cout << "Date                 : " << Date<<endl;
	cout << "Day order of the week: " << DayOrder <<endl;
	cout << "Day                  : " << DetermineDay(DayOrder)<<endl;

	return 0;
}