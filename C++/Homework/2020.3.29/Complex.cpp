/*
homework 13.16 Complex.cpp
*/
#include "Complex.h"
#include <iomanip>
#include <iostream>
using namespace std;
Complex::Complex(void)
    : real(0)
    , imaginary(0) {
}
ostream &operator<<(ostream &output, const Complex &c) {

    output << c.real;
    if (c.imaginary >= 0)
        output << " + ";
    else
        output << " - ";
    output << abs(c.imaginary) << "i\n";
    return output;
}
istream &operator>>(istream &input, Complex &c) {
    int number;
    int multiplier;
    char temp;
    input >> number;
    if (input.peek() == ' ') {
        c.real = number;
        input >> temp;
        multiplier = (temp == '+') ? 1 : -1;
        if (input.peek() != ' ')
            input.clear(ios::failbit);
        else {
            input >> c.imaginary;
            c.imaginary *= multiplier;
            if (input.peek() != 'i') {
                input.clear(ios::failbit);
            } else {
                input.ignore();
            }
        }
    } else if (input.peek() == 'i') {
        input.ignore();
        c.real = 0;
        c.imaginary = number;
    } else if (input.peek() == '\n') {
        c.real = number;
        c.imaginary = 0;
    } else
        input.clear(ios::failbit);
    return input;
}
int main() {
    Complex a, b, c, d, e, f;
    cin >> a >> b >> c >> d;
    cout << a << b << c << d;
}
// this is end
