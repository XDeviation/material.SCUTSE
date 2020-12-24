/*
 * homework 11.10 Package.cpp
 */
#include "Package.h"
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
// this is end
