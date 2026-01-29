//Write a program to convert entered number to text

#include <iostream>
#include <string>


using namespace std;


int ReadNumber(const string& Message) {
	int number;
	do {
		cout << Message << endl;
		cin >> number;
	} while (number < 0);
	return number;
}
string NumberToText(int number) {

    if (number == 0)
        return "Zero";

    string Numbers[20] = {
        "Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine",
        "Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen",
        "Sixteen","Seventeen","Eighteen","Nineteen"
    };

    string Tens[8] = {
        "Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"
    };

    if (number <= 19)
        return Numbers[number];

    else if (number <= 99)
        return (number % 10 != 0)
        ? Tens[number / 10 - 2] + " " + NumberToText(number % 10)
        : Tens[number / 10 - 2];

    else if (number <= 999)
        return (number % 100 != 0)
        ? NumberToText(number / 100) + " Hundred " + NumberToText(number % 100)
        : NumberToText(number / 100) + " Hundred";

    else if (number <= 999999)
        return (number % 1000 != 0)
        ? NumberToText(number / 1000) + " Thousand " + NumberToText(number % 1000)
        : NumberToText(number / 1000) + " Thousand";

    else if (number <= 999999999 )
        return (number % 1000000 != 0)
        ? NumberToText(number / 1000000) + " Million " + NumberToText(number % 1000000)
        : NumberToText(number / 1000000) + " Million";

    return "Number too large";
}
int main() {

	while (1) {
		
		string TextNumber = NumberToText(ReadNumber("Please enter number:"));
		cout << TextNumber << endl;
	}

	return 0;
}