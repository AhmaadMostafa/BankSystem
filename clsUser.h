#pragma once
#include <iostream>
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));

	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#") {
		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName + Seperator;
		UserRecord += User.Password + Seperator;
		UserRecord += to_string(User.Permissions);

		return UserRecord;

	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsUser> _LoadUserDataFromFile() {
		vector<clsUser>vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				vUsers.push_back(_ConvertLinetoUserObject(Line));
			}
			MyFile.close();
		}
		return vUsers;
	}

	void _SaveUsersDataToFile(vector<clsUser>vUser) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		string DataLine;
		if (MyFile.is_open()) {
			for (clsUser& u : vUser) {
				if (!u._MarkedForDelete) {
					DataLine = _ConvertUserObjectToLine(u);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update() {
		vector<clsUser>vUsers = _LoadUserDataFromFile();
		for (clsUser& u : vUsers) {
			if (u.UserName == UserName) {
				u = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew() {
		_AddDataNewLine(_ConvertUserObjectToLine(*this));
	}

	void _AddDataNewLine(string DataLine) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);
		if (MyFile.is_open()){
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}


public:
	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName,
		string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64
	};

	bool isEmpty() {
		return _Mode == enMode::EmptyMode;
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	string GetUserName() {
		return _UserName;
	}

	void SetUserName(string UserName) {
		_UserName = UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName == UserName) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName , string Password) {
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsUser User = _ConvertLinetoUserObject(Line);
				if (User.UserName == UserName && User.Password == Password) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static bool IsUserExist(string UserName)
	{

		clsUser User = clsUser::Find(UserName);
		return (!User.isEmpty());
	}

	static vector <clsUser> GetUsersList() {
		return _LoadUserDataFromFile();
	}

	bool Delete() {
		vector<clsUser>vUser = _LoadUserDataFromFile();
		for (clsUser& u : vUser) {
			if (u.UserName == _UserName) {
				u._MarkedForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUser);

		*this = _GetEmptyUserObject();

		return true;
	}

	bool CheckAccessPermission(enPermissions Permission) {
		if (Permissions == enPermissions::eAll) {
			return true;
		}
		if ((Permission & this->Permissions) == Permission) {
			return true;
		}
		return false;
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	enSaveResults Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
			break;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case clsUser::AddNewMode:
			if(!clsUser::IsUserExist(_UserName)){
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			else
			{
				return enSaveResults::svFaildUserExists;
			}
			break;
		}
	}

};

