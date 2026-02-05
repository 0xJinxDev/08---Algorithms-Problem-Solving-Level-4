//Write a program to read date as string and convert it into struct and vice versa

#include<iostream>
#include<string>

using namespace std;

const string Delim = "/";
short ReadNubmer(const string& Message) {
	short number;
	cout << Message << endl;
	cin >> number;
	return number;
}

string ReadString(const string& Message) {
	string line;
	cout << Message << endl;
	getline(cin >> ws, line);
	return line;
}

struct stDate {
	short Year, Month, Day;
};

void FillDate(string& word, short counter,stDate & Date) {

	switch (counter) {
	case 0: Date.Day = stoi(word); break;
	case 1: Date.Month = stoi(word); break;
	case 2: Date.Year = stoi(word); break;

	}
}
stDate StirngToStruct(const string& line, const string & Delim) {
	stDate Date;
	string word;
	short counter = 0;
	for (int i = 0; i < line.length();) {

		if (line.substr(i, Delim.length()) != Delim) {
			word += line[i];
			i++;
		}
		else {
			if (!word.empty()) {
				FillDate(word, counter, Date);
				counter++;
				word.clear();
			}
			i += Delim.length();
		}

	}
	if (!word.empty()) {
		FillDate(word, counter, Date);
	}

	return Date;
}

string StructToString(const stDate& Date) {
	return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
}

bool IsLeapYear(const stDate& Date) {
	return (Date.Year % 400 == 0) || (Date.Year % 4 == 0 && Date.Year % 100 != 0);
}
short DaysInAMonth(const stDate& Date) {
	if (Date.Month < 1 || Date.Month >12 || Date.Year <= 0) {
		return 0;
	}
	short Months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return (Date.Month == 2) ? IsLeapYear(Date) ? 29 : 28 : Months[Date.Month - 1];
}

bool IsValidDate(const stDate& Date) {
	short days = DaysInAMonth(Date);
	return (days != 0 && Date.Day >= 1 && Date.Day <= days);
}

int main() {
	string Date;
	stDate StructDate;
	do {
		 Date = ReadString("Please enter the date dd/mm/yyyy:");
		 StructDate = StirngToStruct(Date, Delim);
		 if (!IsValidDate(StructDate)) {
			 cout << "Not valid date\n";
		 }
	} while (!IsValidDate(StructDate));


	cout << StructDate.Day << endl;
	cout << StructDate.Month << endl;
	cout << StructDate.Year << endl;

	Date = StructToString(StructDate);
	cout << Date << endl;

}