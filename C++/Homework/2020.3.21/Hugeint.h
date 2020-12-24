/*
homework 10.8 Hugeint.h
*/
#ifndef HUGEINT_H
#define HUGEINT_H
#include <iostream>
#include <string>
using namespace std;
class HugeInt {
    friend ostream &operator<<(ostream &, const HugeInt &);

  public:
    static const int digits = 30;
    HugeInt(long = 0);
    HugeInt(const string &);
    HugeInt operator+(const HugeInt &) const;
    HugeInt operator+(int) const;
    bool operator==(const HugeInt &) const;
    bool operator!=(const HugeInt &) const;
    bool operator<(const HugeInt &) const;
    bool operator<=(const HugeInt &) const;
    bool operator>(const HugeInt &) const;
    bool operator>=(const HugeInt &) const;
    HugeInt operator-(const HugeInt &) const;
    HugeInt operator*(const HugeInt &) const;
    HugeInt operator/(const HugeInt &) const;
    int getLength() const;

  private:
    int negative = 0;
    short integer[digits];
};
#endif
// this is end
