#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"
#include <iomanip>
using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::Readstring();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::Readstring();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::Readstring();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::Readstring();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::Readstring();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

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
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {


            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTransactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        return Permissions;

    }

public:
    static void ShowUpdateUserScreen() {
        _DrawScreenHeader("\tDelete User Screen");
        cout << "\nPlease Enter UserName: ";
        string UserName = clsInputValidate::Readstring();
        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nUserName is not found , choose another one\n";
            UserName = clsInputValidate::Readstring();
        }
        clsUser User = clsUser::Find(UserName);
        _ReadUserInfo(User);
        cout << "\n\nUpdate User Info\n";
        cout << "\n_______________________\n";
        _PrintUser(User);
        clsUser::enSaveResults SaveResults;
        SaveResults = User.Save();
        switch (SaveResults)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Updated Successfully :-)\n";
            _PrintUser(User);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        }

    }


};

