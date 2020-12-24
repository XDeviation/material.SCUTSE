#include <iostream>
using namespace std;
int r, a[100], n;
void dfs(int k) {
    int i;
    if (k > r) {
        for (i = 1; i <= r; i++) {
            cout << a[i] << ' ';
        }
        int a = 1;
        cout << endl;
        return;
    }
    for (i = a[k - 1] + 1; i <= n; i++) {
        a[k] = i;
        dfs(k + 1);
    }
}
int main() {
    cin >> n >> r;
    dfs(1);
    return 0;
}