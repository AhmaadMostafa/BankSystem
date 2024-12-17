#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsUser.h"
#include "Gloabl.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login() {
		bool LoginFailed = false;
		string UserName, Password;
		short trials = 3;
		do
		{
			if (LoginFailed) {
				cout << "\nInvalid UserName/Password!\n";
				cout << "You have " << --trials << " trials to login\n\n";
			}
			if (!trials) {
				cout << "You are locked after 3 failed trials\n\n";
				return false;
			}
			cout << "Enter UserName? ";
			cin >> UserName;
			cout << "Enter Password? ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);
			LoginFailed = CurrentUser.isEmpty();


		} while (LoginFailed);

		clsMainScreen::ShowMainMenue();

		return true;
	}

public:
	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t	Login Screen");
		return _Login();


	}
};

