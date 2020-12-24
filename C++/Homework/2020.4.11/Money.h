/*
 * homework 12.12 Money.h
 */
#include <string>
using namespace std;

class Date {
    friend ostream &operator<<(ostream &, const Date &);

  public:
    Date(int m = 1, int d = 1, int y = 1900);
    void setDate(int, int, int);
    Date &operator++();
    Date operator++(int);
    const Date &operator+=(int);
    bool leapYear(int) const;
    bool endOfMonth(int) const;
    int getMonth() const;

  private:
    int month;
    int day;
    int year;

    static const int days[];
    void helpIncrement();
};

class Employee {
  public:
    Employee(const string &, const string &, const string &, int, int, int);

    void setFirstName(const string &);
    string getFirstName() const;

    void setLastName(const string &);
    string getLastName() const;

    void setSocialSecurityNumber(const string &);
    string getSocialSecurityNumber() const;

    void setBirthDate(int, int, int);
    Date getBirthDate() const;

    virtual double earnings() const = 0;
    virtual void print() const;

  private:
    string firstName;
    string lastName;
    string socialSecurityNumber;
    Date birthDate;
};

class SalariedEmployee : public Employee {
  public:
    SalariedEmployee(const string &, const string &, const string &, int, int,
                     int, double = 0.0);

    void setWeeklySalary(double);
    double getWeeklySalary() const;

    virtual double earnings() const;
    virtual void print() const;

  private:
    double weeklySalary;
};

class CommissionEmployee : public Employee {
  public:
    CommissionEmployee(const string &, const string &, const string &, int, int,
                       int, double = 0.0, double = 0.0);

    void setCommissionRate(double);
    double getCommissionRate() const;

    void setGrossSales(double);
    double getGrossSales() const;

    virtual double earnings() const;
    virtual void print() const;

  private:
    double grossSales;
    double commissionRate;
};

class BasePlusCommissionEmployee : public CommissionEmployee {
  public:
    BasePlusCommissionEmployee(const string &, const string &, const string &,
                               int, int, int, double = 0.0, double = 0.0,
                               double = 0.0);

    void setBaseSalary(double);
    double getBaseSalary() const;

    virtual double earnings() const;
    virtual void print() const;

  private:
    double baseSalary;
};
// this is end
