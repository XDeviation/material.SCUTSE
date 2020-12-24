/*
 * homework 11.9 Account.h
 */
class Account {
  public:
    Account(double);
    ~Account();
    void credit(double);
    bool debit(double);
    void setBalance(double);
    double getBalance();

  private:
    double balance;
};
class CheckingAccount : public Account {
  public:
    CheckingAccount(double, double);
    ~CheckingAccount();
    void credit(double);
    bool debit(double);

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
