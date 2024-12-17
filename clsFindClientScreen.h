#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsString.h"
using namespace std;

class clsFindClientScreen :protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }
public:
    static void ShowFindClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {
            return;
        }
        _DrawScreenHeader("\t Find Client Screen");
        cout << "\nPlease Enter Account Number: ";
        string AccountNumber = clsInputValidate::Readstring();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount number is not found , choose another one\n";
            AccountNumber = clsInputValidate::Readstring();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        cout << "\n Client Was Found\n";
        _PrintClient(Client);
    }
};

