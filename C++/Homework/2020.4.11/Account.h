/*
 * homework 12.14 Account.h
 */
class Account {
  public:
    Account(double);
    ~Account();
    virtual void credit(double);
    virtual bool debit(double);
    void setBalance(double);
    double getBalance();

  private:
    double balance;
};
class CheckingAccount : public Account {
  public:
    CheckingAccount(double, double);
    ~CheckingAccount();
    virtual void credit(double);
    virtual bool debit(double);

  private:
    double transactionFee;
    void chargeFee();
};
class SavingsAccount : public Account {
  public:
    SavingsAccount(double, double);
    ~SavingsAccount();
    double calculateInterest();

  private:
    double interestRate;
};
// this is end
