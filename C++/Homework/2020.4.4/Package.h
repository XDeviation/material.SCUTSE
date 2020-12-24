/*
 * homework 11.10 Package.h
 */
#include <string>
using namespace std;
class Package {
  public:
    Package(const string &, const string &, const string &, const string &, int,
            const string &, const string &, const string &, const string &, int,
            double, double);
    double getWeight() const;
    double getCostPerOunce() const;
    double calculateCost() const;

  private:
    string senderName;
    string senderAddress;
    string senderCity;
    string senderState;
    int senderZIP;
    string recipientName;
    string recipientAddress;
    string recipientCity;
    string recipientState;
    int recipientZIP;
    double weight;
    double costPerOunce;
};

class TwoDayPackage : public Package {
  public:
    TwoDayPackage(const string &, const string &, const string &,
                  const string &, int, const string &, const string &,
                  const string &, const string &, int, double, double, double);

    void setFlatFee(double);
    double getFlatFee() const;
    double calculateCost() const;

  private:
    double flatFee;
};

class OvernightPackage : public Package {
  public:
    OvernightPackage(const string &, const string &, const string &,
                     const string &, int, const string &, const string &,
                     const string &, const string &, int, double, double,
                     double);

    void setOvernightFeePerOunce(double);
    double getOvernightFeePerOunce() const;
    double calculateCost() const;

  private:
    double overnightFeePerOunce;
};
// this is end
