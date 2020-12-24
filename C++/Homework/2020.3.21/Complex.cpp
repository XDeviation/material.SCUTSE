/*
homework 10.8 Complex.cpp
*/
#include "Complex.h"
#include <iostream>
using namespace std;
Complex::Complex(double realPart, double imaginaryPart)
    : real(realPart)
    , imaginary(imaginaryPart) {
}
Complex Complex::operator+(const Complex &operand2) const {
    return Complex(real + operand2.real, imaginary + operand2.imaginary);
}
Complex Complex::operator-(const Complex &operand2) const {
    return Complex(real - operand2.real, imaginary - operand2.imaginary);
}
Complex Complex::operator*(const Complex &operand2) const {
    return Complex(real * operand2.real - imaginary * operand2.imaginary,
                   real * operand2.imaginary + imaginary * operand2.real);
}
bool Complex::operator==(const Complex &operand2) const {
    return real == operand2.real && imaginary == operand2.imaginary;
}
bool Complex::operator!=(const Complex &operand2) const {
    return real != operand2.real || imaginary == operand2.imaginary;
}
Complex &Complex::operator=(const Complex &right) {
    real = right.real;
    imaginary = right.imaginary;
    return *this;
}
ostream &operator<<(ostream &output, const Complex &complex) {
    output << "(" << complex.real << "," << complex.imaginary << ")";
    return output;
}
istream &operator>>(istream &input, Complex &complex) {
    input >> complex.real >> complex.imaginary;
    return input;
}
int main() {
    Complex a, b;
    cin >> a;
    cin >> b; // please input the complex by using  real + ' ' + imaginary
    cout << a << '\n' << b << endl;
    a = a + b;
    b = b - a;
    cout << a << '\n' << b << '\n' << a * b << '\n' << (a == b);
}
// this is end
