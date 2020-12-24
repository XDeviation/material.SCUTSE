#include <iostream>
using namespace std;
int n, use[100], ans[100];
void print() {
    int i;
    for (i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << endl;
}
void dfs(int k) {
    int i;
    if (k == n) {
        print();
        return;
    }
    for (i = 1; i <= n; i++) {
        if (!use[i]) {
            use[i] = 1;
            ans[k + 1] = i;
            dfs(k + 1);
            use[i] = 0;
        }
    }
}
int main() {
    cin >> n;
    dfs(0);
    return 0;
}