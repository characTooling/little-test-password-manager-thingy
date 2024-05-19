// first test
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <windows.h>
using namespace std;


//Main
int main() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	map<string, string> passwords;
    string masterUser = "Toolie", masterPassword = "Cyberlights";
	string username, password, exitcode;
    string keyword = "TOBERANDOMIZEDLATER";
	FILE *userdata, *passdata;
	userdata = fopen("usernames.txt", "a");
	passdata = fopen("passwords.txt", "a");
	if (userdata == NULL) {
		fclose(userdata);
		userdata = fopen("usernames.txt", "w");
		fclose(userdata);
	}
	if (passdata == NULL) {
		fclose(passdata);
		passdata = fopen("passwords.txt", "w");
		fclose(passdata);
	}
	bool exit = false;
	while (exit == false) {
		userdata = fopen("usernames.txt", "a");
		passdata = fopen("passwords.txt", "a");
		cout << "Insert username here: ";
		cin >> username;
		int usernameLength = username.length();
		char* usercharArray = new char[usernameLength + 1];
		strcpy(usercharArray, username.c_str());
		fprintf(userdata, usercharArray);
		cout << "Insert password here: ";
		cin >> password;
		int passLength = password.length();
		char* passcharArray = new char[passLength + 1];
		strcpy(passcharArray, password.c_str());
		fprintf(passdata, passcharArray);
		cout << "Do you want to save more? [Y] [N]";
		cin >> exitcode;
		if (exitcode == "N") {
			exit = true;
			fclose(userdata);
			fclose(passdata);
		}
	}
	map<string, string>::iterator it = passwords.begin();
    string insertedUser, insertedPass;
    cout << "Insert username: ";
    cin >> insertedUser;
    cout << "Insert password: ";
    cin >> insertedPass;
	int remainingAttempts = 3;
    if (insertedUser == masterUser && insertedPass == masterPassword) {
        while (it != passwords.end()) {
            cout << "Username: " << it->first
                << ", Password: " << it->second << endl;
            ++it;
        }
    }
    else {
		while (remainingAttempts > 0) {
			cout << "Insert username: ";
			cin >> insertedUser;
			cout << "Insert password: ";
			cin >> insertedPass;
			if (insertedUser == masterUser && insertedPass == masterPassword) {
				while (it != passwords.end()) {
					cout << "Username: " << it->first
						<< ", Password: " << it->second << endl;
					++it;
				}
				exit;
			}
			else {
				remainingAttempts--;
				if (remainingAttempts != 1) {
					cout << "You have " << remainingAttempts << " attempts left.";
				}
				else {
					cout << "You have 1 attempt left.";
				}
			}
		}
		cout << "You have no access to this data";
    }
	return 0;
}