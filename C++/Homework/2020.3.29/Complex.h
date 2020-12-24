/*
homework 13.16 Complex.h
*/
#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
using namespace std;
class Complex {
    friend ostream &operator<<(ostream &, const Complex &);
    friend istream &operator>>(istream &, Complex &);

  public:
    Complex(void);

  private:
    int real;
    int imaginary;
};
#endif
// this is end
