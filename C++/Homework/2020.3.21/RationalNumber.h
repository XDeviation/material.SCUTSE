/*
homework 10.8 RationalNumber.h
*/
#ifndef RATIONAL_NUMBER_H
#define RATIONAL_NUMBER_H
#include <iostream>
using namespace std;
class RationalNumber {
    friend ostream &operator<<(ostream &output, const RationalNumber &);
    friend istream &operator>>(istream &input, RationalNumber &);

  public:
    RationalNumber(int = 1, int = 1);
    RationalNumber operator+(const RationalNumber &);
    RationalNumber operator-(const RationalNumber &);
    RationalNumber operator*(const RationalNumber &);
    RationalNumber operator/(const RationalNumber &);
    bool operator<(const RationalNumber &) const;
    bool operator>(const RationalNumber &) const;
    bool operator<=(const RationalNumber &) const;
    bool operator>=(const RationalNumber &) const;
    bool operator==(const RationalNumber &) const;
    bool operator!=(const RationalNumber &) const;
    int gcd(int, int);

  private:
    int numerator;
    int denominator;
    void reduction();
};
#endif
// this is end
