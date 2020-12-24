/*
Assignment 3 Matrix.h
*/
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
class Matrix {
    friend ostream &operator<<(ostream &, const Matrix &);
    friend istream &operator>>(istream &, Matrix &);

  private:
    double a, b, c, d;

  public:
    Matrix operator+(const Matrix &) const;
    Matrix operator-(const Matrix &) const;
    Matrix operator*(const Matrix &) const;
    Matrix operator*(const double &) const;
    Matrix &operator*=(const Matrix &);
    Matrix &operator+=(const Matrix &);
    Matrix &operator-=(const Matrix &);
    bool operator==(const Matrix &) const;
    bool operator!=(const Matrix &) const;
    Matrix(double = 1.0, double = 0.0, double = 0.0, double = 1.0);
    ~Matrix();
};
#endif
// this is end.