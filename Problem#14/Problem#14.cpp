//Write a program to check if two dates are equal


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
void ReadDate(stDate& Date) {
	Date.Year = ReadNumber("Please enter the year:");
	Date.Month = ReadNumber("Please enter the month:");
	Date.Day = ReadNumber("Please enter the day:");

}
bool AreTwoDatesEqual(stDate& Date1, stDate& Date2) {

	return (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day);

}
int main() {

	stDate Date1, Date2;

	ReadDate(Date1);
	ReadDate(Date2);

	cout << (AreTwoDatesEqual(Date1, Date2) ? "Yes.\n" : "No.\n");

	return 0;
}
