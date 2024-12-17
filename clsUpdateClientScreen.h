#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsString.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client) {
        cout << "\nEnter First Name: ";
        Client.FirstName = clsInputValidate::Readstring();
        cout << "\nEnter Last Name: ";
        Client.LastName = clsInputValidate::Readstring();
        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::Readstring();
        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::Readstring();
        cout << "\nEnter Pin Code: ";
        Client.PinCode = clsInputValidate::Readstring();
        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();
    }
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
    static void ShowUpdateClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) {
            return;
        }
        _DrawScreenHeader("\t Update Client Screen");
        cout << "\nPlease Enter Client Account Number\n";
        string AccountNumber = clsInputValidate::Readstring();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount number is not found , choose another one\n";
            AccountNumber = clsInputValidate::Readstring();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        cout << "\n\nUpdate Client Info\n";
        cout << "\n_______________________\n";
        _ReadClientInfo(Client);
        clsBankClient::enSaveResults SaveResult;
        SaveResult = Client.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Updated Successfully:-\n";
            break;
        case clsBankClient::enSaveResults::svFailedEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }


};

