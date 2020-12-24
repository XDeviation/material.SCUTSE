/*
homework 10.8 RationalNumber.cpp
*/
#include "RationalNumber.h"
#include <bits/stdc++.h>
using namespace std;
RationalNumber::RationalNumber(int n, int d) {
    numerator = n;
    denominator = d;
    if (denominator < 0) {
        denominator *= -1;
        numerator *= -1;
    }
    if (denominator == 0) denominator = 1;
    reduction();
}
ostream &operator<<(ostream &output, const RationalNumber &a) {
    output << a.numerator << "/" << a.denominator;
    return output;
}
istream &operator>>(istream &input, RationalNumber &a) {
    input >> a.numerator >> a.denominator;
    if (a.denominator < 0) {
        a.denominator *= -1;
        a.numerator *= -1;
    }
    if (a.denominator == 0) a.denominator = 1;
    a.reduction();
    return input;
}
RationalNumber RationalNumber::operator+(const RationalNumber &a) {
    return RationalNumber(numerator * a.denominator + denominator * a.numerator,
                          denominator * a.denominator);
}
RationalNumber RationalNumber::operator-(const RationalNumber &a) {
    return RationalNumber(numerator * a.denominator - denominator * a.numerator,
                          denominator * a.denominator);
}
RationalNumber RationalNumber::operator*(const RationalNumber &a) {
    return RationalNumber(numerator * a.numerator, denominator * a.denominator);
}
RationalNumber RationalNumber::operator/(const RationalNumber &a) {
    if (a.numerator != 0) {
        return RationalNumber(numerator * a.denominator,
                              denominator * a.numerator);
    } else {
        cout << "ERROR:Div by zero" << endl;
        exit(1);
    }
}
bool RationalNumber::operator<(const RationalNumber &a) const {
    return this->numerator * a.denominator < this->denominator * a.numerator;
}
bool RationalNumber::operator>(const RationalNumber &a) const {
    return a < *this;
}
bool RationalNumber::operator<=(const RationalNumber &a) const {
    return !(*this > a);
}
bool RationalNumber::operator>=(const RationalNumber &a) const {
    return !(*this < a);
}
bool RationalNumber::operator==(const RationalNumber &a) const {
    return numerator == a.numerator && denominator == a.denominator;
}
bool RationalNumber::operator!=(const RationalNumber &a) const {
    return !(*this == a);
}
int RationalNumber::gcd(int a, int b) {
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}
void RationalNumber::reduction() {
    int p = gcd(abs(numerator), abs(denominator));
    numerator /= p;
    denominator /= p;
}
int main() {
    RationalNumber a, b;
    cin >> a >> b;
    cout << a << '\n' << b << endl;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << a / b;
}
// this is end
