#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;


class clsBankClient : public clsPerson
{

public:
	enum enMode {
		EmptyMode = 0, UpdateMode = 1, AddNewMode = 2
	};

private:
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seprator = "#//#") {
		vector<string>vClientData = clsString::Split(Line, Seprator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stod(vClientData[6]));
	}
	
	static string _ConvertClientObjectToLine(clsBankClient Client , string seprator = "#//#") {
		string Record;
		Record += Client.FirstName + seprator;
		Record += Client.LastName + seprator;
		Record += Client.Email + seprator;
		Record += Client.Phone + seprator;
		Record += Client.AccountNumber() + seprator;
		Record += Client.PinCode + seprator;
		Record += to_string(Client.AccountBalance);

		return Record;
	}

	static vector<clsBankClient>_LoadDataClientFromFile() {
		vector<clsBankClient>vClient;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // read only
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClient.push_back(Client);
			}
			MyFile.close();
		}
		return vClient;
	}

	static void _SaveClientDataToFile(vector<clsBankClient>vClient) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		string DataLine;
		if (MyFile.is_open()) {
			for (clsBankClient& i : vClient) {
				if (!i._MarkedForDelete) {
					DataLine = _ConvertClientObjectToLine(i);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _Update() {
		vector<clsBankClient>vClient;
		vClient = _LoadDataClientFromFile();
		for (clsBankClient& i : vClient) {
			if (i.AccountNumber() == AccountNumber()) {
				i = *this;
				break;
			}
		}
		_SaveClientDataToFile(vClient);
	}

	void _AddDataLineToFile(string Line) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);
		if (MyFile.is_open()) {
			MyFile << Line << endl;
			MyFile.close();
		}

	}

	void _AddNew() {
		return _AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, double AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone) 
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string Code) {
		_PinCode = Code;
	}

	string GetPinCode() {
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	
	void SetAccountBalance(double Balance) {
		_AccountBalance = Balance;
	}

	double GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	static clsBankClient Find(string AccountNumber) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); // read only

		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}
	
	static clsBankClient Find(string AccountNumber , string PinCode) {
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	bool Delete() {
		vector<clsBankClient> vClient = _LoadDataClientFromFile();
		for (clsBankClient& i : vClient) {
			if (i.AccountNumber() == _AccountNumber) {
				i._MarkedForDelete = true;
				break;
			}
		}
		_SaveClientDataToFile(vClient);
		*this = _GetEmptyClientObject();
		return true;

	}

	static vector<clsBankClient> GetClientsList() {
		return _LoadDataClientFromFile();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.isEmpty());
	}

	static clsBankClient GetAddNewLineObject(string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static double GetTotalBalances() {
		vector<clsBankClient>vClient = _LoadDataClientFromFile();
		double balance = 0;
		for (clsBankClient& i : vClient) {
			balance += i.AccountBalance;
		}
		return balance;
	}

	enum enSaveResults {svFailedEmptyObject = 0 , svSucceeded = 1 , svFaildAccountNumberExists = 2};

	enSaveResults Save() {
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFailedEmptyObject;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
			
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		if (_AccountBalance < Amount) {
			return false;
		}
		_AccountBalance -= Amount;
		Save();
		return true;
	}

};

