#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"
#include "clsString.h"
using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nAcc. Number : " << User.Permissions;
        cout << "\n___________________\n";
    }

public:
    static void ShowFindUserScreen() {
        _DrawScreenHeader("\tFind User Screen");
        cout << "\nPlease Enter UserName: ";
        string UserName = clsInputValidate::Readstring();
        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nUserName is not found , choose another one\n";
            UserName = clsInputValidate::Readstring();
        }
        clsUser User = clsUser::Find(UserName);
        cout << "\n User Was Found\n";
        _PrintUser(User);
    }
};

