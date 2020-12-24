/*
Assignment 3 MatrixMain.cpp
*/
#include "Matrix.h"
#include <bits/stdc++.h>
using namespace std;
int main() {
    Matrix a, b(2, 3, 4, 5);
    cout << "a = " << a << endl << "b = " << b << endl;
    Matrix c;
    cin >> c;
    cout << "c * 2.0 = " << c * 2.0 << endl;
    cout << (a == c) << ' ' << (a != c) << endl;
    Matrix d(2, 3, 4, 5);
    cout << (b == d) << ' ' << (b != d) << endl;
    a *= b;
    b += c;
    c -= d;
    cout << "a = " << a << "\nb = " << b << "\nc = " << c << endl;
}
// this is end.