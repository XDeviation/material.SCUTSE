#include <iostream>
using namespace std;
int a[1000];
int loc(int i, int j, int c) {
    return (i * (i + 1) / 2 + j) * c;
}
int main() {
    int c, row, column;
    cin >> c >> row >> column;
    if (row >= column) {
        cout << loc(row, column, c);
    } else {
        cout << loc(column, row, c);
    }
}
/*
默认 l1 = l2 = 0
*/