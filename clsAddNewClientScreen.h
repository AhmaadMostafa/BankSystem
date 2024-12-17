#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen : public clsScreen
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
    static void ShowAddNewClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
            return;
        }
        _DrawScreenHeader("\t Add New Client Screen");
        cout << "\nPlease Enter Account Number: ";
        string AccountNumber = clsInputValidate::Readstring();
        while (clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::Readstring();
        }
        clsBankClient NewClient = clsBankClient::GetAddNewLineObject(AccountNumber);
        _ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();
        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svFailedEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
            cout << "\nError account was not saved because account number is used!\n";
            break;
        case clsBankClient::enSaveResults::svSucceeded:
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        default:
            break;
        }
    }

};

