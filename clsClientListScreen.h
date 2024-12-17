#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>
#include <string>
using namespace std;
#pragma once

class clsClientListScreen : public clsScreen
{
private:
    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }
public:
    static void ShowClientsList() {

        if (!CheckAccessRights(clsUser::enPermissions::pListClients)) {
            return;
        }
        vector<clsBankClient>vClient = clsBankClient::GetClientsList();
        string Title = "\t Client List Screen";
        string SubTitle = "\t + (" + to_string(vClient.size()) + ") Clients(s) , ";
        _DrawScreenHeader(Title , SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        if (!vClient.size()) {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
        {
            for (clsBankClient& i : vClient) {
                _PrintClientRecordLine(i);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }



};

