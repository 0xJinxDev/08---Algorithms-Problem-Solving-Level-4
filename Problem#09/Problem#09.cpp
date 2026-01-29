//Write a program to print year calender


#include <iostream>
#include <string>
#include <iomanip>


using namespace std;

short ReadNumber(const string& Message) {

	short number;
	do {
		cout << Message << endl;
		cin >> number;
	} while (number <= 0);
	return number;
}

short CalculateDayOrder(const short year, const short month, const short day) {

	int a = (14 - month) / 12;
	int y = year - a;
	int m = month + (12 * a) - 2;

	short d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	return d;
}

bool IsLeapYear(const short year) {
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

short DaysInAMonth(const short year, const short month) {

	if (month < 1 || month >12) {
		return 0;
	}

	const short Months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (month == 2) ? (IsLeapYear(year) ? 29 : 28) : Months[month - 1];
}

string MonthName(const short month)
{
	switch (month)
	{
	case 1:  return "Jan";
	case 2:  return "Feb";
	case 3:  return "Mar";
	case 4:  return "Apr";
	case 5:  return "May";
	case 6:  return "Jun";
	case 7:  return "Jul";
	case 8:  return "Aug";
	case 9:  return "Sep";
	case 10: return "Oct";
	case 11: return "Nov";
	case 12: return "Dec";
	default:
		return "Invalid Month";
	}
}
void FillDays(int arr[6][7], const short Rows, const short Cols, const short month, const short year) {

	short DayOrder = CalculateDayOrder(year, month, 1);
	short NumberOfDays = DaysInAMonth(year, month);
	short counter = 1;
	for (short i = 0; i < Rows; i++)
		for (short j = 0; j < Cols; j++)
			arr[i][j] = 0;

	for (short i = 0; i < Rows; i++) {
		if (i == 0) {
			for (short j = DayOrder; j < Cols; j++) {
				if (counter <= NumberOfDays) {
					arr[i][j] = counter;
				}

				counter++;
			}
		}
		else {
			for (short j = 0; j < Cols; j++) {
				if (counter <= NumberOfDays) {
					arr[i][j] = counter;
				}
				counter++;
			}
		}

	}


}
void PrintArray(const int arr[5][7], const short Rows, const short Cols) {

	for (short i = 0; i < Rows; i++) {
		for (short j = 0; j < Cols; j++) {

			if (arr[i][j] != 0) {
				cout << setw(5) << arr[i][j];
			}
			else {
				cout << setw(5) << " ";
			}


		}
		cout << endl;
	}

}
void PrintCalender(const short month, short year, int arr[6][7]) {

	cout << "________________ " << MonthName(month) << " ________________" << endl;
	cout << setw(5) << "Sun" << setw(5) << "Mon" << setw(5) << "Tue" << setw(5) << "Wed" << setw(5) << "Thu" << setw(5) << "Fri" << setw(5) << "Sat" << endl;
	FillDays(arr, 6, 7, month, year);
	PrintArray(arr, 6, 7);
	cout << "_____________________________________";
	cout << endl;
}
void PrintYearCalender(const short year, int arr[6][7]) {

	for (int i = 1; i <= 12; i++) {
		PrintCalender(i, year, arr);
	}

}

int main() {
	short year = ReadNumber("Please enter the year:");
	int arr[6][7] = {};


	PrintYearCalender(year, arr);

	return 0;
}