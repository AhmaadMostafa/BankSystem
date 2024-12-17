#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsString.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen
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
    static string _ReadAccountNumber() {
        cout << "\nPlease Enter Account Number: ";
        string AccountNumber = clsInputValidate::Readstring();
        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nClient with [" << AccountNumber << "] does not exist\n";
            cout << "Please enter Account Number: ";
            AccountNumber = clsInputValidate::Readstring();
        }
        return AccountNumber;
    }

public:
    static void ShowWithdrawScreen() {
        _DrawScreenHeader("\t  Withdraw Screen");
        string AccountNumber = _ReadAccountNumber();
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        double Amount = 0;
        cout << "\nPlease Enter Withdraw Amount: \n";
        Amount = clsInputValidate::ReadDblNumber();
        char operation = 'n';
        cout << "\nAre you sure you want to perform this transaction? ";
        cin >> operation;
        if (operation == 'y' || operation == 'Y') {
            if (Client.Withdraw(Amount)) {
                cout << "\nAmount Withdrew Successfully.\n";
                cout << "\nNew Balance Is: " << Client.AccountBalance;
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client.AccountBalance;

            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }
};

