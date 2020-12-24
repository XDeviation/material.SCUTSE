/*
homework 10.8 Complex.h
*/
#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
using namespace std;
class Complex {
    friend ostream &operator<<(ostream &output, const Complex &);
    friend istream &operator>>(istream &input, Complex &);

  public:
    Complex(double = 0.0, double = 0.0);
    Complex operator+(const Complex &) const;
    Complex operator-(const Complex &) const;
    Complex operator*(const Complex &) const;
    Complex &operator=(const Complex &);
    bool operator==(const Complex &) const;
    bool operator!=(const Complex &) const;

  private:
    double real;
    double imaginary;
};
#endif
// this is end
