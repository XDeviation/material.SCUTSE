/*
 * homework 12.12 Money.cpp
 */
#include "Money.h"
#include <bits/stdc++.h>
using namespace std;

Employee::Employee(const string &first, const string &last, const string &ssn,
                   int month, int day, int year)
    : firstName(first)
    , lastName(last)
    , socialSecurityNumber(ssn)
    , birthDate(month, day, year) {
}

void Employee::setFirstName(const string &first) {
    firstName = first;
}

string Employee::getFirstName() const {
    return firstName;
}

void Employee::setLastName(const string &last) {
    lastName = last;
}

string Employee::getLastName() const {
    return lastName;
}

void Employee::setSocialSecurityNumber(const string &ssn) {
    socialSecurityNumber = ssn;
}

string Employee::getSocialSecurityNumber() const {
    return socialSecurityNumber;
}

void Employee::setBirthDate(int month, int day, int year) {
    birthDate.setDate(month, day, year);
}

Date Employee::getBirthDate() const {
    return birthDate;
}

void Employee::print() const {
    cout << getFirstName() << ' ' << getLastName()
         << "\nbirthday: " << getBirthDate()
         << "\nsocial security number: " << getSocialSecurityNumber();
}

SalariedEmployee::SalariedEmployee(const string &first, const string &last,
                                   const string &ssn, int month, int day,
                                   int year, double salary)
    : Employee(first, last, ssn, month, day, year) {
    setWeeklySalary(salary);
}

void SalariedEmployee::setWeeklySalary(double salary) {
    weeklySalary = (salary < 0.0) ? 0.0 : salary;
}

double SalariedEmployee::getWeeklySalary() const {
    return weeklySalary;
}

double SalariedEmployee::earnings() const {
    return getWeeklySalary();
}

void SalariedEmployee::print() const {
    cout << "salaried employee: ";
    Employee::print();
    cout << "\nweekly salary: " << getWeeklySalary();
}

CommissionEmployee::CommissionEmployee(const string &first, const string &last,
                                       const string &ssn, int month, int day,
                                       int year, double sales, double rate)
    : Employee(first, last, ssn, month, day, year) {
    setGrossSales(sales);
    setCommissionRate(rate);
}

void CommissionEmployee::setCommissionRate(double rate) {
    commissionRate = ((rate > 0.0 && rate < 1.0) ? rate : 0.0);
}

double CommissionEmployee::getCommissionRate() const {
    return commissionRate;
}

void CommissionEmployee::setGrossSales(double sales) {
    grossSales = ((sales < 0.0) ? 0.0 : sales);
}

double CommissionEmployee::getGrossSales() const {
    return grossSales;
}

double CommissionEmployee::earnings() const {
    return getCommissionRate() * getGrossSales();
}

void CommissionEmployee::print() const {
    cout << "commission employee: ";
    Employee::print();
    cout << "\ngross sales: " << getGrossSales()
         << "; commission rate: " << getCommissionRate();
}

BasePlusCommissionEmployee::BasePlusCommissionEmployee(
    const string &first, const string &last, const string &ssn, int month,
    int day, int year, double sales, double rate, double salary)
    : CommissionEmployee(first, last, ssn, month, day, year, sales, rate) {
    setBaseSalary(salary);
}

void BasePlusCommissionEmployee::setBaseSalary(double salary) {
    baseSalary = ((salary < 0.0) ? 0.0 : salary);
}

double BasePlusCommissionEmployee::getBaseSalary() const {
    return baseSalary;
}

double BasePlusCommissionEmployee::earnings() const {
    return getBaseSalary() + CommissionEmployee::earnings();
}

void BasePlusCommissionEmployee::print() const {
    cout << "base-salaried ";
    CommissionEmployee::print();
    cout << "; base salary: " << getBaseSalary();
}

const int Date::days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date(int m, int d, int y) {
    setDate(m, d, y);
}

void Date::setDate(int mm, int dd, int yy) {
    month = (mm >= 1 && mm <= 12) ? mm : 1;
    year = (yy >= 1900 && yy <= 2100) ? yy : 1900;

    if (month == 2 && leapYear(year))
        day = (dd >= 1 && dd <= 29) ? dd : 1;
    else
        day = (dd >= 1 && dd <= days[month]) ? dd : 1;
}

Date &Date::operator++() {
    helpIncrement();
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    helpIncrement();

    return temp;
}

const Date &Date::operator+=(int additionalDays) {
    for (int i = 0; i < additionalDays; i++)
        helpIncrement();

    return *this;
}

bool Date::leapYear(int testYear) const {
    if (testYear % 400 == 0 || (testYear % 100 != 0 && testYear % 4 == 0))
        return true;
    else
        return false;
}

int Date::getMonth() const {
    return month;
}

bool Date::endOfMonth(int testDay) const {
    if (month == 2 && leapYear(year))
        return testDay == 29;
    else
        return testDay == days[month];
}

void Date::helpIncrement() {

    if (!endOfMonth(day))
        day++;
    else if (month < 12) {
        month++;
        day = 1;
    } else {
        year++;
        month = 1;
        day = 1;
    }
}

ostream &operator<<(ostream &output, const Date &d) {
    static char *monthName[13] = {
        "",        "January",  "February", "March",  "April",
        "May",     "June",     "July",     "August", "September",
        "October", "November", "December"};
    output << monthName[d.month] << ' ' << d.day << ", " << d.year;
    return output;
}

int main() {
    vector<Employee *> employees(3);
    employees[0] =
        new SalariedEmployee("Azuki", "Azusa", "111-11-1111", 1, 1, 2000, 800);
    employees[1] = new CommissionEmployee("Suki", "zaki", "222-22-2222", 2, 2,
                                          1998, 10000, .06);
    employees[2] = new BasePlusCommissionEmployee("S", "B", "333-33-3333", 2,
                                                  27, 2010, 5000, .04, 300);
    int month = 1;
    for (month; month <= 12; month++) {
        for (size_t i = 0; i < employees.size(); i++) {
            employees[i]->print();
            cout << endl;
            Date birthday = employees[i]->getBirthDate();
            if (birthday.getMonth() == month)
                cout << "Birthday: " << (employees[i]->earnings() + 100.0)
                     << endl;
            else
                cout << "Common day: " << employees[i]->earnings() << endl;
            cout << endl;
        }
    }
}
// this is end