#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsDeleteClientScreen :protected clsScreen
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
    static void ShowDeleteClientScreen(){
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
            return;
        }
        _DrawScreenHeader("\tDelete Client Screen");
        cout << "\nPlease Enter Account Number: ";
        string AccountNumber = clsInputValidate::Readstring();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount number is not found , choose another one\n";
            AccountNumber = clsInputValidate::Readstring();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        cout << "\nAre you sure you want to delete this client\n";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            if (Client.Delete()) {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }

};

