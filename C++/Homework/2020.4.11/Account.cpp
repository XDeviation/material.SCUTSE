/*
 * homework 12.14 Account.cpp
 */
#include "Account.h"
#include <bits/stdc++.h>
using namespace std;

Account::Account(double initialBalance) {
    balance = max(initialBalance, 0.0);
}

Account::~Account() = default;

void Account::credit(double amount) {
    balance = balance + amount;
}

bool Account::debit(double amount) {
    if (amount > balance) {
        cout << "穷" << endl;
        return false;
    } else {
        balance = balance - amount;
        return true;
    }
}

void Account::setBalance(double newBalance) {
    balance = newBalance;
}

double Account::getBalance() {
    return balance;
}

SavingsAccount::SavingsAccount(double initialBalance, double rate)
    : Account(initialBalance) {
    interestRate = max(rate, 0.0);
}

SavingsAccount::~SavingsAccount() = default;

double SavingsAccount::calculateInterest() {
    return getBalance() * interestRate;
}

CheckingAccount::CheckingAccount(double initialBalance, double fee)
    : Account(initialBalance) {
    transactionFee = max(fee, 0.0);
}

CheckingAccount::~CheckingAccount() = default;

void CheckingAccount::credit(double amount) {
    Account::credit(amount);
    chargeFee();
}

bool CheckingAccount::debit(double amount) {
    bool success = Account::debit(amount);
    if (success) {
        chargeFee();
        return true;
    } else
        return false;
}

void CheckingAccount::chargeFee() {
    Account::setBalance(getBalance() - transactionFee);
}
int main() {
    vector<Account *> accounts(4);
    accounts[0] = new SavingsAccount(10, 0.1);
    accounts[1] = new CheckingAccount(20, 0.1);
    accounts[2] = new SavingsAccount(30, 0.01);
    accounts[3] = new CheckingAccount(114514, 0.001);
    cout << fixed << setprecision(2);
    for (size_t i = 0; i < accounts.size(); i++) {
        cout << "现有: " << accounts[i]->getBalance() << '\n';
        double withdrawalAmount = 0.0;
        cout << "取" << i + 1 << ": ";
        cin >> withdrawalAmount;
        accounts[i]->debit(withdrawalAmount);
        double depositAmount = 0.0;
        cout << "存" << i + 1 << ": ";
        cin >> depositAmount;
        accounts[i]->credit(depositAmount);
        SavingsAccount *savingsAccountPtr =
            dynamic_cast<SavingsAccount *>(accounts[i]);
        cout << "现有: " << accounts[i]->getBalance() << "\n";
    }
}
// this is end.
