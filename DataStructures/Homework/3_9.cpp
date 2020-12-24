#include <bits/stdc++.h>
using namespace std;
map<string, int> coefficient;
struct T {
    string x;
    int coef;
};
vector<T> ans;
int main() {
    int x;
    string s;
    while (cin >> x >> s) {
        coefficient[s] += x;
    }
    for (auto it : coefficient) {
        ans.push_back({it.first, it.second});
    }
    sort(ans.begin(), ans.end(), [](T &x, T &y) { return x.x > y.x; });
    for (auto it : ans) {
        if (it.x == "0" || it.coef == 0) continue;
        cout << it.coef << it.x << ' ';
    }
}
/*
1 x^2 2 x^2 -3 x^2 4 x 5 0 6 x^3 7 x^3 8 x^4

x^4 13x^3 4x
*/