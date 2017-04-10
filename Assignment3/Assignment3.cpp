/* 
Michael Shearer
Assignment 3
Professor Kelo
29 March, 2017
*/

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

//BANK ACCOUNT BASE CLASS//
class BankAccount {
protected:
	double accountNumber;
	double accountBalance;
public:
	BankAccount();
	void Deposit();
	void Withdraw();
};
//BANK ACCOUNT DEFAULT CONSTRUCTOR//
BankAccount :: BankAccount() {
	accountBalance = 0.0;
}
//SAVINGS ACCOUNT SUBCLASS//
class SavingsAccount : public BankAccount {
	float APR;
	void calculateInterest(double bal);
	double savingsWithFee = 2.00;
public:
	SavingsAccount();
	void captureAccount();
	void Display();
};
//testcomment
//SAVINGS ACCOUNT DEFAULT CONSTRUCTOR//
SavingsAccount::SavingsAccount() {
	accountBalance = 0;
}
//CHECKING ACCOUNT SUBCLASS//
class CheckingAccount : public BankAccount {
public:
	CheckingAccount();
	void captureAccount();
	void Display();
};
//CHECKING ACCOUNT DEFAULT CONSTRUCTOR//
CheckingAccount::CheckingAccount() {
	accountBalance = 0;
}
//CD ACCOUNT SUBCLASS//
class CertDepAccount : public BankAccount {
	int termLength;
	int yearsPassed;
	double intEarnedRate;
public:
	CertDepAccount();
	void captureAccount();
	void Display();
};

CertDepAccount::CertDepAccount() {
	accountBalance = 0;
}

//GET USER INPUT FUNCTION//
void SavingsAccount::captureAccount() {
	cout << "Enter Account Number: ";
	cin >> accountNumber;
	cout << "Enter the balance: ";
	cin >> accountBalance;
	cin.clear();
	cin.ignore();
	if (accountBalance < 10,000) {
		APR = 0.1;
	}
	else {
		APR = 0.2;
	}
}
void CheckingAccount::captureAccount() {
	cout << "Enter Account Number: ";
	cin >> accountNumber;
	cout << "Enter the balance: ";
	cin >> accountBalance;
	if (accountBalance < 500) {
		accountBalance -= 5;
	}
	cin.clear();
	cin.ignore();
}
void CertDepAccount::captureAccount() {
	cout << "Enter the account number: " << endl;
	cin >> accountNumber;
	cout << "Enter the account balance: " << endl;
	cin >> accountBalance;
	cout << "Enter the term length in years: " << endl;
	cin >> termLength;
	if (termLength >= 5) {
		intEarnedRate = 0.1;
	}
	else {
		intEarnedRate = 0.05;
	}
}
//OVERLOADED DISPLAY FUNCTIONS//
void SavingsAccount :: Display() {
	cout << "The account number is " << accountNumber << "Balance: " << accountBalance << endl;
}

void CheckingAccount :: Display() {
	cout << "The account number is " << accountNumber << "Balance: " << accountBalance << endl;
}

void CertDepAccount :: Display() {
	cout << "The account number is " << accountNumber << "Balance: " << accountBalance << endl;
}

//WITHDRAWL FUNCTION//
void BankAccount::Withdraw() {
	double withAmount;
	cout << "How much would you like to withdraw? " << endl;
	cin >> withAmount;
	accountBalance -= withAmount;
}

//DEPOSIT FUNCTION//
void BankAccount::Deposit() {
	double depAmount;
	cout << "How much would you like to deposit? " << endl;
	cin >> depAmount;
	accountBalance += depAmount;
}

void SavingsAccount :: calculateInterest(double bal) {
	double interest;
	double balanceIN;

	balanceIN = bal;

	if (balanceIN >= 10,000) {
		APR = 0.02;
		accountBalance += (APR*accountBalance);
	}
	else {
		APR = 0.01;
		accountBalance += (APR*accountBalance);
	}
}

//MAIN FUNCTION//
int main()
{
	string createAccount;
	int numAccounts;
	
	BankAccount **alist;
	int count;

	cout << "How many accounts would you like to create? " << endl;
	cin >> count;

	alist = new BankAccount*[count];


	cout << "Would you like to create an account? Y/N " << endl;
	cin >> createAccount;

	while ((createAccount == "y") || (createAccount == "Y")) {
		char accountType;
		for (int i = 0; i < count; i++) {
			cout << "What type of account would you like to create?\n(S)Savings\n(C)Checking\n(D)Certificate of Deposit" << endl;
			cin >> accountType;
			switch (accountType) {
				case 's':
				case 'S':
					alist[i] = new SavingsAccount();
					numAccounts++;
					alist[i]->captureAccount();
					char modifyType;
					cout << "Would you like to (D)Deposit or (W)Withdraw from this account? Press 'N' to quit." << endl;
					cin >> modifyType;
					switch (modifyType) {
					case 'd':
					case 'D':
						alist[i]->Deposit();
						alist[i]->calculateInterest();
					case 'w':
					case 'W':
						alist[i]->Withdraw();
						alist[i].accountBalance -= 2;
						alist[i]->calculateInterest();
					case 'n':
					case 'N':
						break;
					}
				case 'c':
				case 'C':
					alist[i] = new CheckingAccount();
					numAccounts++;
					alist[i]->captureAccount();
					char modifyType;
					cout << "Would you like to (D)Deposit, (W)Withdraw, or (O)Order Checks form this account? Press 'N' to quit." << endl;
					cin >> modifyType;
					switch (modifyType) {
					case 'd':
					case 'D':
						alist[i]->Deposit();
						if (alist[i].accountBalance < 500) {
							alist[i].accountBalance -= 5;
						}
					case 'w':
					case 'W':
						alist[i]->Withdraw();
						if (alist[i].accountBalance < 500) {
							alist[i].accountBalance -= 5;
						}
					case 'o':
					case 'O':
						alist[i].accountBalance -= 15;
						if (alist[i].accountBalance < 500) {
							alist[i].accountBalance -= 5;
						}
					case 'n':
					case 'N':
						break;
					}
				case 'd':
				case 'D':
					alist[i] = new CertDepAccount();
					numAccounts++;
					alist[i]->captureAccount();
					char modifyType;
					cout << "Would you like to (D)Deposit or (W)Withdraw from this account? Press 'N' to quit." << endl;
					cin >> modifyType;
					switch (modifyType) {
					case 'd':
					case 'D':
						alist[i]->Deposit();
					case 'w':
					case 'W':
						alist[i]->Withdraw();
						if (alist[i].yearsPassed < alist[i].termLength) {
							alist[i].accountBalance -= (alist[i].accountBalance*0.1);
						}
					case 'n':
					case 'N':
						break;
					}
			}
			cin.clear();
			cin.ignore();
		}
	}
	for (int i = 0; i < count; i++) {
		alist[i]->Display();
	}
	for (int i = 0; i < count; i++) {
		delete alist[i];
	}
	delete alist;

    return 0;
}




