#include <iostream>
using namespace std;
int main() {
    double a, b;
    cin >> a >> b;
    double ans = (b * b * b - a * a * a) / 3 + b - a;
    cout << ans;
}