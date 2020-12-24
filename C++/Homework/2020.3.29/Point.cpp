/*
homework 13.15 Point.cpp
*/
#include "Point.h"
#include <iostream>
using namespace std;
ostream &operator<<(ostream &output, const Point &p) {
    output << "(" << p.xCoordinate << ", " << p.yCoordinate << ")";
    return output;
}
istream &operator>>(istream &input, Point &p) {
    if (input.peek() != '(')
        input.clear(ios::failbit);
    else {
        input.ignore();
        input >> p.xCoordinate;
        if (input.peek() != ',')
            input.clear(ios::failbit);
        else {
            input.ignore();
            input >> p.yCoordinate;
            if (input.peek() != ')')
                input.clear(ios::failbit);
            else
                input.ignore();
        }
    }
    return input;
}
int main() {
    Point a, b;
    cin >> a >> b;
    cout << a << '\n' << b;
}
// this is end
