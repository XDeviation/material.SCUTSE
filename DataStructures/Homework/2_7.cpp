#include <iostream>
using namespace std;
const int maxn = 1e3 + 7;
struct T {
    int last, len;
} b[maxn];
int a[maxn];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i].last = 0, b[i].len = 1;
    }
    int ans = 0, last = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i] && b[j].len >= b[i].len) {
                b[i].last = j;
                b[i].len = b[j].len + 1;
            }
        }
        if (b[i].len > ans) {
            ans = b[i].len;
            last = i;
        }
    }
    while (last) {
        cout << a[last] << ' ';
        last = b[last].last;
    }
}