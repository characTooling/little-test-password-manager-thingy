// first test
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include <windows.h>
using namespace std;
struct passwordComb {
	string site;
	string username;
	string password;
};

//Main
int main() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	int lim = 94;
	map<int, passwordComb> passwords;
    string masterUser = "Toolie", masterPassword = "Cyberlights";
	string username, password, site, exitcode;
	FILE *userdata, *passdata, *sitedata;
	userdata = fopen("usernames.txt", "a");
	passdata = fopen("passwords.txt", "a");
	sitedata = fopen("sites.txt", "a");
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
	if (sitedata == NULL) {
		fclose(sitedata);
		sitedata = fopen("sites.txt", "w");
		fclose(sitedata);
	}
	int counter = 1;
	bool exit = false;
	while (exit == false) {
		passwordComb passwordCombination;
		userdata = fopen("usernames.txt", "a");
		passdata = fopen("passwords.txt", "a");
		sitedata = fopen("sites.txt", "a");
		cout << "Insert site here: ";
		cin >> site;
		passwordCombination.site = site;
		int siteLength = site.length();
		char* sitecharArray = new char[siteLength + 1];
		strcpy(sitecharArray, site.c_str());
		fprintf(userdata, sitecharArray);
		cout << "Insert username here: ";
		cin >> username;
		passwordCombination.username = username;
		int usernameLength = username.length();
		char* usercharArray = new char[usernameLength + 1];
		strcpy(usercharArray, username.c_str());
		fprintf(userdata, usercharArray);
		string generation;
		cout << "Do you have a password already? [Y]/[N] ";
		cin >> generation;
		if (generation == "N") {
			int passLength;
			cout << "How long do you want the password to be? ";
			cin >> passLength;
			string password;
			char* passcharArray = new char[passLength + 1];
			for (int i = 0; i < passLength; i++) {
				int asciiValue = rand() % lim + 33;
				password += char(asciiValue);
				passcharArray[i] = char(asciiValue);
			}

			strcpy(passcharArray, password.c_str());
			fprintf(passdata, passcharArray);
			passwordCombination.password = password;
		}
		else {
			cout << "Insert password here: ";
			cin >> password;
			int passLength = password.length();
			char* passcharArray = new char[passLength + 1];
			strcpy(passcharArray, password.c_str());
			fprintf(passdata, passcharArray);
			passwordCombination.password = password;
		}
		passwords[counter] = {passwordCombination};
		counter++;
		cout << "Do you want to save more? [Y] [N]";
		cin >> exitcode;
		if (exitcode == "N") {
			exit = true;
			fclose(userdata);
			fclose(passdata);
		}
	}
	map<int, passwordComb>::iterator it = passwords.begin();
    string insertedUser, insertedPass;
	insertedUser = masterUser;
	insertedPass = masterPassword;
	int remainingAttempts = 3;
    if (insertedUser == masterUser && insertedPass == masterPassword) {
        while (it != passwords.end()) {
            cout << "Site: " << (it->second).site << ", Username: " << (it->second).username
                << ", Password: " << (it->second).password << endl;
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
					cout << "Site: " << (it->second).site << ", Username: " << (it->second).username
						<< ", Password: " << (it->second).password << endl;
					++it;
				}
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