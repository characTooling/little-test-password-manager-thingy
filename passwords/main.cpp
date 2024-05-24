// first test
#include <iostream>
#include <fstream>
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
	ofstream userdata, passdata, sitedata;
	userdata.open("usernames.txt", ios::ate);
	passdata.open("passwords.txt", ios::ate);
	sitedata.open("sites.txt", ios::ate);
	int counter = 1;
	bool exit = false;
	while (exit == false) {
		passwordComb passwordCombination;
		cout << "Insert site here: ";
		cin >> site;
		passwordCombination.site = site;
		sitedata << site << '\n';
		cout << "Insert username here: ";
		cin >> username;
		passwordCombination.username = username;
		userdata << username << '\n';
		string generation;
		cout << "Do you have a password already? [Y]/[N] ";
		cin >> generation;
		if (generation == "N") {
			int passLength;
			cout << "How long do you want the password to be? ";
			cin >> passLength;
			string password;
			for (int i = 0; i < passLength; i++) {
				int asciiValue = rand() % lim + 33;
				password += char(asciiValue);
			}
			passdata << password << '\n';
			passwordCombination.password = password;
		}
		else {
			cout << "Insert password here: ";
			cin >> password;
			passdata << password << '\n';
			passwordCombination.password = password;
		}
		passwords[counter] = {passwordCombination};
		counter++;
		cout << "Do you want to save more? [Y] [N]";
		cin >> exitcode;
		if (exitcode == "N") {
			exit = true;
			sitedata.close();
			userdata.close();
			passdata.close();
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