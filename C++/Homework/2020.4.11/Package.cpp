/*
 * homework 12.13 Package.cpp
 */
#include "Package.h"
#include <bits/stdc++.h>
Package::Package(const string &sName, const string &sAddress,
                 const string &sCity, const string &sState, int sZIP,
                 const string &rName, const string &rAddress,
                 const string &rCity, const string &rState, int rZIP, double w,
                 double cost)
    : senderName(sName)
    , senderAddress(sAddress)
    , senderCity(sCity)
    , senderState(sState)
    , senderZIP(sZIP)
    , recipientName(rName)
    , recipientAddress(rAddress)
    , recipientCity(rCity)
    , recipientState(rState)
    , recipientZIP(rZIP) {
}
double Package::getWeight() const {
    return weight;
}

double Package::getCostPerOunce() const {
    return costPerOunce;
}
double Package::calculateCost() const {
    return weight * costPerOunce;
}

TwoDayPackage::TwoDayPackage(const string &sName, const string &sAddress,
                             const string &sCity, const string &sState,
                             int sZIP, const string &rName,
                             const string &rAddress, const string &rCity,
                             const string &rState, int rZIP, double w,
                             double cost, double fee)
    : Package(sName, sAddress, sCity, sState, sZIP, rName, rAddress, rCity,
              rState, rZIP, w, cost) {
    setFlatFee(fee);
}

void TwoDayPackage::setFlatFee(double fee) {
    flatFee = fee;
}

double TwoDayPackage::calculateCost() const {
    return Package::calculateCost() + flatFee;
}

OvernightPackage::OvernightPackage(const string &sName, const string &sAddress,
                                   const string &sCity, const string &sState,
                                   int sZIP, const string &rName,
                                   const string &rAddress, const string &rCity,
                                   const string &rState, int rZIP, double w,
                                   double cost, double fee)
    : Package(sName, sAddress, sCity, sState, sZIP, rName, rAddress, rCity,
              rState, rZIP, w, cost) {
    setOvernightFeePerOunce(fee);
}

void OvernightPackage::setOvernightFeePerOunce(double overnightFee) {
    overnightFeePerOunce = overnightFee;
}

double OvernightPackage::calculateCost() const {
    return getWeight() * (getCostPerOunce() + overnightFeePerOunce);
}

int main() {
    vector<Package *> packages(3);
    packages[0] =
        new Package("A", "1", "3", "4", 1, "B", "2", "5", "6", 2, 1.1, 0.1);
    packages[1] = new TwoDayPackage("C", "51", "3", "321", 3, "2", "321", "41",
                                    "54", 4, 132, 2.2, 0.2);
    packages[2] = new OvernightPackage("F", "gfd", "5", "3423", 5, "G", "6",
                                       "5", "4", 6, 41, 3.3, 0.3);
    double totalShippingCost = 0.0;
    for (size_t i = 0; i < packages.size(); i++) {
        double cost = packages[i]->calculateCost();
        cout << cost << "\n";
        totalShippingCost += cost;
    }
    cout << "tot: " << totalShippingCost << endl;
}
// this is end
