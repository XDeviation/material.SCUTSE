/*
Assignment 3 Matrix.cpp
*/
#include "Matrix.h"
#include <bits/stdc++.h>
using namespace std;
Matrix::Matrix(double A, double B, double C, double D)
    : a(A)
    , b(B)
    , c(C)
    , d(D) {
}
Matrix::~Matrix() = default;
Matrix Matrix::operator+(const Matrix &m2) const {
    return Matrix(a + m2.a, b + m2.b, c + m2.c, d + m2.d);
}
Matrix Matrix::operator-(const Matrix &m2) const {
    return Matrix(a - m2.a, b - m2.b, c - m2.c, d - m2.d);
}
Matrix Matrix::operator*(const Matrix &m2) const {
    return Matrix(a * m2.a + b * m2.c, a * m2.b + b * m2.d, c * m2.a + d * m2.c,
                  c * m2.b + d * m2.d);
}
Matrix Matrix::operator*(const double &i) const {
    return Matrix(a * i, b * i, c * i, d * i);
}
Matrix &Matrix::operator*=(const Matrix &right) {
    Matrix a = *this;
    *this = a * right;
    return *this;
}
Matrix &Matrix::operator+=(const Matrix &right) {
    Matrix a = *this;
    *this = a + right;
    return *this;
}
Matrix &Matrix::operator-=(const Matrix &right) {
    Matrix a = *this;
    *this = a - right;
    return *this;
}
bool Matrix::operator==(const Matrix &m2) const {
    return a == m2.a && b == m2.b && c == m2.c && d == m2.d;
}
bool Matrix::operator!=(const Matrix &m2) const {
    return !(*this == m2);
}
ostream &operator<<(ostream &output, const Matrix &matrix) {
    output << matrix.a << " " << matrix.b << " " << matrix.c << " " << matrix.d;
    return output;
}
istream &operator>>(istream &input, Matrix &matrix) {
    input >> matrix.a >> matrix.b >> matrix.c >> matrix.d;
    return input;
}
// this is end.