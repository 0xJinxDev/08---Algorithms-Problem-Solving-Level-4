// Project #01 bank project extension 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const string ClientsFile = "Clients.txt";
const string UsersFile = "Users.txt";
const string Delim = "/##/";



struct stClient {
	string AccountNumber;
	string Name;
	int age;
	float balance;
	bool Delete = false;
};
struct stUsers {
	string UserName;
	string Password;
	short privilege;
	bool Delete = false;
};
enum enAction {
	ToPrintClients = 1, ToAddClient = 2, ToDeleteClient = 3, ToUpdateClient = 4,
	ToFindClient = 5, ToDoTransaction = 6, ToManageUsers = 7, ToLogout = 8
};
enum enTransactinoAction {
	ToDeposit = 1, ToWithdraw = 2, ToShowTotalBalance = 3, ToGoBackToMainMenu = 4
};
enum enType {
	Users = 1, Clients = 2
};
enum enManageUsers {
	ToListUsers = 1, ToAddUser = 2, ToDeleteUser = 3, ToUpdateUser = 4, ToFindUser = 5, GoBackToMainMenu = 6
};
enum enPermissions
{
	pShowClientList = 1 << 0,
	pAddNewClient = 1 << 1,
	pDeleteClient = 1 << 2,
	pUpdateClient = 1 << 3,
	pFindClient = 1 << 4,
	pTransactions = 1 << 5,
	pManageUsers = 1 << 6
};

void PrintMainMenu(const string& Username, short privilege);
stUsers FindUser(const vector <stUsers>& vUsers, const string& Username);

bool CheckPermission(short privilege, enPermissions permission) {
	return (privilege & permission) == permission;
}

bool IsAdmin(short privilege) {
	short allPermissions = pShowClientList | pAddNewClient | pDeleteClient | pUpdateClient | pFindClient | pTransactions | pManageUsers;
	return privilege == allPermissions;
}

string ReadString(const string& Message) {
	cout << Message << endl;
	string line;
	getline(cin >> ws, line);
	return line;
}
int ReadInt(const string& Message) {
	cout << Message << endl;
	int num;
	cin >> num;
	cin.ignore();
	return num;
}
float ReadFloat(const string& Message) {
	cout << Message << endl;
	float f;
	cin >> f;
	cin.ignore();
	return f;
}
void GoBackToMainMenue(const string& Username, short privilege)
{
	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause>0");
	PrintMainMenu(Username, privilege);
}
void GoBackToTrasnaction()
{
	cout << "\n\nPress any key to go back to Transactions Menu...";
	system("pause>0");

}
string ClientRecordToLine(const stClient& c) {
	return c.AccountNumber + Delim +
		c.Name + Delim +
		to_string(c.age) + Delim +
		to_string(c.balance);
}

string UserRecordToLine(const stUsers& u) {
	return u.UserName + Delim +
		u.Password + Delim +
		to_string(u.privilege);
}

string RecordToLine(enType type, const stClient& c = {}, const stUsers& u = {}) {
	return (type == Clients)
		? ClientRecordToLine(c)
		: UserRecordToLine(u);
}
void SaveToFile(const string& line, const string& FileName, bool overwrite = false) {
	fstream MyFile;
	MyFile.open(FileName, overwrite ? ios::out : ios::out | ios::app);
	if (MyFile.is_open()) {

		MyFile << line << endl;
		MyFile.close();
	}
	else {
		cout << "Error opening the file." << endl;
		return;
	}
}

void PrintMainMenu(const string& Username, short privilege) {
	system("cls");
	const int width = 53;
	string welcome = " Welcome " + Username + " ";
	int totalEquals = width - welcome.length();
	int leftEquals = totalEquals / 2;
	int rightEquals = totalEquals - leftEquals;

	cout << string(leftEquals, '=') << welcome << string(rightEquals, '=') << endl;

	if (CheckPermission(privilege, pShowClientList))
		cout << "[1] Show Client List." << endl;
	if (CheckPermission(privilege, pAddNewClient))
		cout << "[2] Add New Client." << endl;
	if (CheckPermission(privilege, pDeleteClient))
		cout << "[3] Delete Client." << endl;
	if (CheckPermission(privilege, pUpdateClient))
		cout << "[4] Update Client Info." << endl;
	if (CheckPermission(privilege, pFindClient))
		cout << "[5] Find Client." << endl;
	if (CheckPermission(privilege, pTransactions))
		cout << "[6] Transactions." << endl;
	if (CheckPermission(privilege, pManageUsers))
		cout << "[7] Manage users" << endl;

	cout << "[8] Logout." << endl;

	cout << string(width, '=') << endl;
}

void PrintClients(const vector <stClient>& vClients) {
	cout << "Total Number of Clients is: " << vClients.size() << endl;
	cout << left << setw(25) << "Account Number" << setw(25) << "Name" << setw(15) << "Age" << setw(15) << "Balance" << endl;
	for (const stClient& Client : vClients) {

		cout << left << setw(25) << Client.AccountNumber << setw(25) << Client.Name << setw(15) << Client.age << setw(15) << Client.balance << endl;
	}
	if (vClients.empty()) {
		cout << "No clients found.\n";
		return;
	}
}
void FindClient(string& ClientNumber, const vector <stClient>& vClients) {
	bool Found = false;
	cout << left << setw(25) << "Account Number" << setw(25) << "Name" << setw(15) << "Age" << setw(15) << "Balance" << endl;
	for (const stClient& Client : vClients) {
		if (ClientNumber == Client.AccountNumber) {
			cout << left << setw(25) << Client.AccountNumber << setw(25) << Client.Name << setw(15) << Client.age << setw(15) << Client.balance << endl;
			Found = true;

		}
	}

	if (!Found) {
		cout << "Client not found!\n";
	}
}
bool isRegistered(const string& AccountNumber, const vector<stClient>& vClients) {
	for (const stClient& c : vClients) {
		if (AccountNumber == c.AccountNumber)
			return true;
	}
	return false;
}
stClient ReadClient(const vector <stClient>& vClients, bool Update = false) {
	stClient tmpClient;

	tmpClient.AccountNumber = ReadString("Please enter account number:");
	while (isRegistered(tmpClient.AccountNumber, vClients) && !Update) {
		cout << "The account already exists.\n";
		tmpClient.AccountNumber = ReadString("Please enter account number:");
	}
	tmpClient.Name = ReadString("Please enter client's name:");
	tmpClient.age = ReadInt("Please enter client's age:");
	tmpClient.balance = ReadFloat("Please enter client's balance:");
	return tmpClient;
}


void DeleteClient(vector <stClient>& vClients) {
	string line;
	bool FirstRecord = true;
	bool NoRecords = true;
	for (stClient& c : vClients) {

		if (!c.Delete) {
			NoRecords = false;
			line = RecordToLine(Clients, c);
			SaveToFile(line, ClientsFile, FirstRecord ? true : false);
			FirstRecord = false;
		}
	}
	if (NoRecords) {
		line.clear();
		SaveToFile(line, ClientsFile, NoRecords);
	}

}
void UpdateFile(vector<stClient>& vClients) {
	string line;
	bool FirstRecord = true;
	for (stClient& c : vClients) {
		line = RecordToLine(Clients, c);
		SaveToFile(line, ClientsFile, FirstRecord ? true : false);
		FirstRecord = false;
	}
}
void MarkToBeDeleted(string& AccountNumber, vector <stClient>& vClients) {

	for (stClient& c : vClients) {
		if (AccountNumber == c.AccountNumber) {
			c.Delete = true;
		}
	}
}

void FillClientsVector(const string& word, vector<stClient>& vClients, const short counter, stClient& c) {
	switch (counter) {
	case 0: c.AccountNumber = word; break;
	case 1: c.Name = word; break;
	case 2: c.age = stoi(word); break;
	case 3: c.balance = stof(word); break;
	}
	if (counter == 3)
		vClients.push_back(c);
}

void FillUsersVector(const string& word, vector<stUsers>& vUsers, const short counter, stUsers& u) {
	switch (counter) {
	case 0: u.UserName = word; break;
	case 1: u.Password = word; break;
	case 2: u.privilege = stoi(word); break;
	}
	if (counter == 2)
		vUsers.push_back(u);
}
void FillVector(const string& word, vector<stClient>& vClients, vector<stUsers>& vUsers, const short counter, stClient& c, stUsers& u, enType type) {

	switch (type) {
	case Users: FillUsersVector(word, vUsers, counter, u); break;
	case Clients: FillClientsVector(word, vClients, counter, c); break;
	}

}

void LineToRecord(const string& line, vector<stClient>& vClients, vector <stUsers>& vUsers, enType type) {
	string word;
	short counter = 0;
	stClient tmpClient{};
	stUsers tmpUser{};
	for (size_t i = 0; i < line.length();) {
		if (line.substr(i, Delim.length()) != Delim) {
			word += line[i];
			i++;
		}
		else {
			if (!word.empty()) {
				FillVector(word, vClients, vUsers, counter, tmpClient, tmpUser, type);
				counter++;
				word.clear();
			}
			i += Delim.length();
		}
	}

	if (!word.empty()) {
		FillVector(word, vClients, vUsers, counter, tmpClient, tmpUser, type);
	}
}


void UpdateVector(vector <stClient>& vClients, vector <stUsers>& vUsers, const string& FileName, enType type) {

	type == Clients ? vClients.clear() : vUsers.clear();

	fstream MyFile;
	MyFile.open(FileName, ios::in);
	string line;
	if (MyFile.is_open()) {

		while (getline(MyFile, line)) {

			LineToRecord(line, vClients, vUsers, type);
		}

		MyFile.close();
	}

}


void VectorToFile(vector <stClient>& vClients, vector <stUsers>& vUsers, enAction Action, enType type) {

	switch (Action) {

	case ToDeleteClient: DeleteClient(vClients); cout << "Client Deleted successfully!\n"; UpdateVector(vClients, vUsers, ClientsFile, type); break;
	case ToUpdateClient: UpdateFile(vClients); cout << "Client Updated Successfully~\n"; UpdateVector(vClients, vUsers, ClientsFile, type); break;
	}


}

void Deletion(vector <stClient>& vClients, vector <stUsers>& vUsers, enType type) {
	PrintClients(vClients);
	char Flag;
	string AccountNumber;
	cout << "Please enter the account number you want to delete:" << endl;
	getline(cin, AccountNumber);
	FindClient(AccountNumber, vClients);
	if (isRegistered(AccountNumber, vClients)) {
		cout << "Are you sure you want to delete this account?(y/n)" << endl;
		cin >> Flag;
		cin.ignore();
		if (Flag == 'Y' || Flag == 'y') {
			MarkToBeDeleted(AccountNumber, vClients);
			VectorToFile(vClients, vUsers, ToDeleteClient, type);
		}
	}
	else {
		cout << "Client not found!\n";
	}

	PrintClients(vClients);

}
void UpdateClientInfo(const string& AccountNumber, vector<stClient>& vClients) {

	for (stClient& c : vClients) {

		if (c.AccountNumber == AccountNumber) {
			c = ReadClient(vClients, true);

		}
	}
}
void UpdateClient(vector <stClient>& vClients, vector <stUsers>& vUsers, enType type) {
	PrintClients(vClients);
	char Flag;
	string AccountNumber;
	cout << "Please enter the account number you want to update:" << endl;
	getline(cin, AccountNumber);
	FindClient(AccountNumber, vClients);
	if (isRegistered(AccountNumber, vClients)) {
		cout << "Are you sure you want to update this account?(y/n)" << endl;
		cin >> Flag;
		cin.ignore();
		if (Flag == 'Y' || Flag == 'y') {
			UpdateClientInfo(AccountNumber, vClients);

			VectorToFile(vClients, vUsers, ToUpdateClient, type);
		}
	}
	PrintClients(vClients);

}

void SearchForClient(const vector<stClient>& vClients) {
	string AccountNumber = ReadString("Please enter the account number you want to search for");
	FindClient(AccountNumber, vClients);

}

void AddClient(vector<stClient>& vClients) {
	stClient c = ReadClient(vClients);
	vClients.push_back(c);
	string line = RecordToLine(Clients, c);
	SaveToFile(line, ClientsFile);
	cout << "Client Added successfully!\n";
}

void ShowTransactionsMenu() {
	system("cls");
	cout << "=====================================================" << endl;
	cout << "[1] Deposit." << endl;
	cout << "[2] Withdraw." << endl;
	cout << "[3] Total Balance." << endl;
	cout << "[4] Go to Main Menu." << endl;
	cout << "=====================================================" << endl;
	cout << endl << endl;
}

void ShowManageUsersMenu() {
	system("cls");
	cout << "=====================================================" << endl;
	cout << "                   Manage Users                      " << endl;
	cout << "=====================================================" << endl;
	cout << "[1] List Users." << endl;
	cout << "[2] Add New User." << endl;
	cout << "[3] Delete User." << endl;
	cout << "[4] Update User." << endl;
	cout << "[5] Find User." << endl;
	cout << "[6] Go to Main Menu." << endl;
	cout << "=====================================================" << endl;
}

void Deposit(vector <stClient>& vClients) {
	PrintClients(vClients);
	string AccountID = ReadString("Please enter account ID:");
	if (isRegistered(AccountID, vClients)) {
		FindClient(AccountID, vClients);
		int Amount = ReadInt("Please enter the amount you want to deposit:");

		for (stClient& c : vClients) {

			if (c.AccountNumber == AccountID) {
				c.balance += Amount;
				UpdateFile(vClients);
				cout << "Balance updated successfully!\n";
			}
		}


	}
	else {
		cout << "Client not found!\n";
	}
	GoBackToTrasnaction();
}
void Withdraw(vector <stClient>& vClients) {
	PrintClients(vClients);
	string AccountID = ReadString("Please enter account ID:");
	if (isRegistered(AccountID, vClients)) {
		FindClient(AccountID, vClients);
		int Amount = ReadInt("Please enter the amount you want to withdraw:");

		for (stClient& c : vClients) {

			if (c.AccountNumber == AccountID) {
				c.balance -= Amount;
				UpdateFile(vClients);
				cout << "Balance updated successfully!\n";
			}
		}


	}
	else {
		cout << "Client not found!\n";
	}
	GoBackToTrasnaction();
}
float TotalBalances(vector <stClient>& vClients) {
	PrintClients(vClients);

	float TotalBalance = 0;

	for (stClient& c : vClients) {
		TotalBalance += c.balance;
	}

	return TotalBalance;
}
void ChoiceTransaction(vector <stClient>& vClients, vector <stUsers>& vUsers, enTransactinoAction Action) {
	switch (Action) {
	case ToDeposit: system("cls"); Deposit(vClients); UpdateVector(vClients, vUsers, ClientsFile, Clients); break;
	case ToWithdraw: system("cls"); Withdraw(vClients); UpdateVector(vClients, vUsers, ClientsFile, Clients); break;
	case ToShowTotalBalance: system("cls"); cout << TotalBalances(vClients) << endl; GoBackToTrasnaction(); break;
	}
}
void Transactions(vector <stClient>& vClients, vector <stUsers>& vUsers) {
	enTransactinoAction Action;
	do {
		ShowTransactionsMenu();

		Action = (enTransactinoAction)ReadInt("Choose what do you want to do? [1 to 4]?");
		ChoiceTransaction(vClients, vUsers, Action);
	} while (Action != ToGoBackToMainMenu);
}

void ListUsers(const vector<stUsers>& vUsers) {
	cout << "\n=====================================================" << endl;
	cout << "                    Users List                       " << endl;
	cout << "=====================================================" << endl;
	cout << "Total Number of Users: " << vUsers.size() << endl;
	cout << left << setw(25) << "Username" << setw(20) << "Password" << setw(15) << "Privileges" << setw(10) << "Type" << endl;
	cout << "-----------------------------------------------------" << endl;

	for (const stUsers& u : vUsers) {
		string userType = IsAdmin(u.privilege) ? "[ADMIN]" : "";
		cout << left << setw(25) << u.UserName
			<< setw(20) << u.Password
			<< setw(15) << u.privilege
			<< setw(10) << userType << endl;
	}

	if (vUsers.empty()) {
		cout << "No users found.\n";
	}
	cout << "=====================================================" << endl;
}

short ReadPrivileges()
{
	short privileges = 0;
	int choice;

	cout << "\n=====================================================" << endl;
	cout << "                Select Permissions                   " << endl;
	cout << "=====================================================" << endl;
	cout << "[1] Show Client List\n";
	cout << "[2] Add New Client\n";
	cout << "[3] Delete Client\n";
	cout << "[4] Update Client Info\n";
	cout << "[5] Find Client\n";
	cout << "[6] Transactions\n";
	cout << "[7] Manage Users\n";
	cout << "[8] All Permissions\n";
	cout << "[0] Finish\n";
	cout << "=====================================================" << endl;

	do
	{
		choice = ReadInt("Enter permission number (0 to finish):");

		short permission = 0;

		switch (choice)
		{
		case 1: permission = pShowClientList; break;
		case 2: permission = pAddNewClient; break;
		case 3: permission = pDeleteClient; break;
		case 4: permission = pUpdateClient; break;
		case 5: permission = pFindClient; break;
		case 6: permission = pTransactions; break;
		case 7: permission = pManageUsers; break;
		case 8:
			privileges = pShowClientList | pAddNewClient | pDeleteClient | pUpdateClient | pFindClient | pTransactions | pManageUsers;
			cout << "All permissions granted!\n";
			return privileges;
		case 0: break;
		default:
			cout << "Invalid choice!\n";
			continue;
		}

		if (choice != 0 && choice != 8)
		{
			if (privileges & permission) {
				cout << "Privilege already added!\n";
			}
			else {
				privileges |= permission;
				cout << "Privilege added successfully.\n";
			}
		}

	} while (choice != 0);

	return privileges;
}

bool IsUserExists(const string& Username, const vector<stUsers>& vUsers) {
	for (const stUsers& u : vUsers) {
		if (u.UserName == Username)
			return true;
	}
	return false;
}

stUsers ReadUser(const vector<stUsers>& vUsers, bool Update = false)
{
	stUsers TempUser;

	TempUser.UserName = ReadString("Please enter the username:");

	while (IsUserExists(TempUser.UserName, vUsers) && !Update) {
		cout << "Username already exists! Please choose another username.\n";
		TempUser.UserName = ReadString("Please enter the username:");
	}

	TempUser.Password = ReadString("Please enter the password:");
	TempUser.privilege = ReadPrivileges();

	return TempUser;
}

void AddUser(vector<stUsers>& vUsers) {
	cout << "\n=====================================================" << endl;
	cout << "                   Add New User                      " << endl;
	cout << "=====================================================" << endl;

	stUsers u = ReadUser(vUsers);
	vUsers.push_back(u);
	string line = RecordToLine(Users, {}, u);
	SaveToFile(line, UsersFile, false);

	cout << "\n>>> User added successfully! <<<\n";
}

void MarkUserToDelete(vector <stUsers>& vUsers, const string& UserToDelete) {
	for (stUsers& User : vUsers) {
		if (User.UserName == UserToDelete) {
			User.Delete = true;
		}
	}
}

void UpdateUsersFile(const vector <stUsers>& vUsers) {
	string line;
	bool FirstRecord = true;
	bool NoRecords = true;

	for (const stUsers& user : vUsers) {
		if (!user.Delete) {
			line = RecordToLine(Users, {}, user);
			SaveToFile(line, UsersFile, FirstRecord);
			FirstRecord = false;
			NoRecords = false;
		}
	}

	if (NoRecords) {
		line.clear();
		SaveToFile(line, UsersFile, NoRecords);
	}
}

void DeleteUser(vector <stUsers>& vUsers) {
	cout << "\n=====================================================" << endl;
	cout << "                   Delete User                       " << endl;
	cout << "=====================================================" << endl;

	ListUsers(vUsers);

	while (true) {
		cout << "\nEnter username to delete (or type 'back' to return): ";
		string UserToDelete;
		getline(cin >> ws, UserToDelete);

		if (UserToDelete == "back" || UserToDelete == "BACK") {
			cout << "Returning to Manage Users menu...\n";
			return;
		}

		stUsers User = FindUser(vUsers, UserToDelete);

		if (User.UserName == "##") {
			cout << "\n>>> User '" << UserToDelete << "' not found! <<<\n";
			cout << "Please enter a valid username from the list above.\n";
		}
		else if (IsAdmin(User.privilege)) {
			cout << "\n>>> Access Denied! You cannot delete an Admin user. <<<\n";
			cout << "Admin users have full permissions and cannot be deleted.\n";
		}
		else {
			char confirm;
			cout << "\nAre you sure you want to delete user '" << UserToDelete << "'? (y/n): ";
			cin >> confirm;
			cin.ignore();

			if (confirm == 'Y' || confirm == 'y') {
				MarkUserToDelete(vUsers, UserToDelete);
				UpdateUsersFile(vUsers);

				cout << "\n>>> User '" << UserToDelete << "' deleted successfully! <<<\n";
				return;
			}
			else {
				cout << "Deletion cancelled.\n";
				return;
			}
		}
	}
}

void UpdateUserInfo(const string& Username, vector<stUsers>& vUsers) {
	for (stUsers& u : vUsers) {
		if (u.UserName == Username) {
			cout << "\nUpdating user '" << Username << "':\n";
			u.Password = ReadString("Please enter new password:");
			u.privilege = ReadPrivileges();
			break;
		}
	}
}

void UpdateUser(vector<stUsers>& vUsers) {
	cout << "\n=====================================================" << endl;
	cout << "                   Update User                       " << endl;
	cout << "=====================================================" << endl;

	ListUsers(vUsers);

	while (true) {
		cout << "\nEnter username to update (or type 'back' to return): ";
		string Username;
		getline(cin >> ws, Username);

		if (Username == "back" || Username == "BACK") {
			cout << "Returning to Manage Users menu...\n";
			return;
		}

		stUsers User = FindUser(vUsers, Username);

		if (User.UserName == "##") {
			cout << "\n>>> User '" << Username << "' not found! <<<\n";
			cout << "Please enter a valid username from the list above.\n";
		}
		else if (IsAdmin(User.privilege)) {
			cout << "\n>>> Access Denied! You cannot update an Admin user. <<<\n";
			cout << "Admin users have full permissions and cannot be modified.\n";
		}
		else {
			char confirm;
			cout << "\nAre you sure you want to update user '" << Username << "'? (y/n): ";
			cin >> confirm;
			cin.ignore();

			if (confirm == 'Y' || confirm == 'y') {
				UpdateUserInfo(Username, vUsers);
				UpdateUsersFile(vUsers);

				cout << "\n>>> User '" << Username << "' updated successfully! <<<\n";
				return;
			}
			else {
				cout << "Update cancelled.\n";
				return;
			}
		}
	}
}

void SearchForUser(const vector<stUsers>& vUsers) {
	cout << "\n=====================================================" << endl;
	cout << "                    Find User                        " << endl;
	cout << "=====================================================" << endl;

	while (true) {
		cout << "\nEnter username to search (or type 'back' to return): ";
		string Username;
		getline(cin >> ws, Username);

		if (Username == "back" || Username == "BACK") {
			cout << "Returning to Manage Users menu...\n";
			return;
		}

		stUsers User = FindUser(vUsers, Username);

		if (User.UserName == "##") {
			cout << "\n>>> User '" << Username << "' not found! <<<\n";
		}
		else {
			cout << "\n=====================================================" << endl;
			cout << "                   User Details                      " << endl;
			cout << "=====================================================" << endl;
			cout << left << setw(25) << "Username" << setw(20) << "Password" << setw(15) << "Privileges" << endl;
			cout << "-----------------------------------------------------" << endl;
			cout << left << setw(25) << User.UserName
				<< setw(20) << User.Password
				<< setw(15) << User.privilege << endl;
			cout << "=====================================================" << endl;

			cout << "\nPress any key to continue...";
			system("pause>0");
			return;
		}
	}
}

void ChoiceManageUsers(vector <stUsers>& vUsers, enManageUsers Action, vector <stClient>& vClients) {
	switch (Action) {
	case ToListUsers:
		system("cls");
		ListUsers(vUsers);
		cout << "\nPress any key to continue...";
		system("pause>0");
		break;

	case ToAddUser:
		system("cls");
		AddUser(vUsers);
		cout << "\nPress any key to continue...";
		system("pause>0");
		break;

	case ToDeleteUser:
		system("cls");
		DeleteUser(vUsers);
		UpdateVector(vClients, vUsers, UsersFile, Users);
		cout << "\nPress any key to continue...";
		system("pause>0");
		break;

	case ToUpdateUser:
		system("cls");
		UpdateUser(vUsers);
		UpdateVector(vClients, vUsers, UsersFile, Users);
		cout << "\nPress any key to continue...";
		system("pause>0");
		break;

	case ToFindUser:
		system("cls");
		SearchForUser(vUsers);
		break;

	case GoBackToMainMenu:
		break;

	default:
		cout << "Invalid choice! Please enter from 1 to 6." << endl;
		system("pause>0");
		break;
	}
}

void ManageUsers(vector <stUsers>& vUsers, vector <stClient>& vClients) {
	enManageUsers Action;
	do {
		ShowManageUsersMenu();
		Action = (enManageUsers)ReadInt("\nChoose what do you want to do? [1 to 6]:");
		ChoiceManageUsers(vUsers, Action, vClients);
	} while (Action != GoBackToMainMenu);
}

void Choice(vector<stClient>& vClients, vector <stUsers>& vUsers, enAction Action, const string& Username, short privilege) {
	switch (Action) {
	case ToPrintClients:
		if (CheckPermission(privilege, pShowClientList)) {
			system("cls");
			PrintClients(vClients);
			GoBackToMainMenue(Username, privilege);
		}
		else {
			cout << "\n>>> Access Denied! You don't have permission to view client list. <<<\n";
			system("pause>0");
		}
		break;

	case ToAddClient:
		if (CheckPermission(privilege, pAddNewClient)) {
			system("cls");
			AddClient(vClients);
			GoBackToMainMenue(Username, privilege);
		}
		else {
			cout << "\n>>> Access Denied! You don't have permission to add clients. <<<\n";
			system("pause>0");
		}
		break;

	case ToDeleteClient:
		if (CheckPermission(privilege, pDeleteClient)) {
			system("cls");
			Deletion(vClients, vUsers, Clients);
			GoBackToMainMenue(Username, privilege);
		}
		else {
			cout << "\n>>> Access Denied! You don't have permission to delete clients. <<<\n";
			system("pause>0");
		}
		break;

	case ToUpdateClient:
		if (CheckPermission(privilege, pUpdateClient)) {
			system("cls");
			UpdateClient(vClients, vUsers, Clients);
			GoBackToMainMenue(Username, privilege);
		}
		else {
			cout << "\n>>> Access Denied! You don't have permission to update clients. <<<\n";
			system("pause>0");
		}
		break;

	case ToFindClient:
		if (CheckPermission(privilege, pFindClient)) {
			system("cls");
			SearchForClient(vClients);
			GoBackToMainMenue(Username, privilege);
		}
		else {
			cout << "\n>>> Access Denied! You don't have permission to find clients. <<<\n";
			system("pause>0");
		}
		break;

	case ToDoTransaction:
		if (CheckPermission(privilege, pTransactions)) {
			system("cls");
			Transactions(vClients, vUsers);
		}
		else {
			cout << "\n>>> Access Denied! You don't have permission to access transactions. <<<\n";
			system("pause>0");
		}
		break;

	case ToManageUsers:
		if (CheckPermission(privilege, pManageUsers)) {
			system("cls");
			ManageUsers(vUsers, vClients);
		}
		else {
			cout << "\n>>> Access Denied! You don't have permission to manage users. <<<\n";
			system("pause>0");
		}
		break;

	case ToLogout:
		break;

	default:
		cout << "Please enter from 1 to 8." << endl;
		break;
	}
}

stUsers FindUser(const vector <stUsers>& vUsers, const string& Username) {
	for (const stUsers& u : vUsers) {
		if (u.UserName == Username) {
			return u;
		}
	}
	return stUsers{ "##","##",0 };
}

bool ShouldLogin(const string& Username, const string& Password, const vector<stUsers>& vUsers) {
	stUsers user = FindUser(vUsers, Username);
	return user.UserName != "##" && user.Password == Password;
}

int main() {
	vector <stClient> vClients;
	vector <stUsers> vUsers;
	enAction Action;
	UpdateVector(vClients, vUsers, UsersFile, Users);
	UpdateVector(vClients, vUsers, ClientsFile, Clients);
	string Username, Password;
	bool PrintInvalid = false;

	while (1) {
		system("cls");
		cout << "================ Login ================\n";
		if (PrintInvalid)
			cout << "Invalid username or password.\n";
		Username = ReadString("Please enter your username:");
		Password = ReadString("Please enter your passsword:");

		PrintInvalid = true;
		if (ShouldLogin(Username, Password, vUsers)) {
			PrintInvalid = false;
			stUsers CurrentUser = FindUser(vUsers, Username);
			do {
				PrintMainMenu(Username, CurrentUser.privilege);
				Action = (enAction)ReadInt("Choose what do you want to do? [1 to 8]?");
				Choice(vClients, vUsers, Action, Username, CurrentUser.privilege);

			} while (Action != ToLogout);
		}
	}
	return 0;
}
