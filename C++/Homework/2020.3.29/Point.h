/*
homework 13.15 Point.h
*/
#ifndef POINT_H
#define POINT_H
#include <iostream>
using namespace std;
class Point {
    friend ostream &operator<<(ostream &, const Point &);
    friend istream &operator>>(istream &, Point &);

  private:
    int xCoordinate;
    int yCoordinate;
};
#endif
// this is end
