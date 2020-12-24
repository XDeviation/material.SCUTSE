/*
 * homework 11.9 Account.cpp
 */
#include "Account.h"
#include <cmath>
#include <iostream>
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
        cout << "Debit amount exceeded account balance." << endl;
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
// this is end.
