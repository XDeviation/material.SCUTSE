#include <iostream>
using namespace std;
string a[100], b[100];
int n;
void dfs(int now, int tot, int dep, string ans, string stuck[100]) {
    string tmp[100];
    for (int i = 1; i <= tot; i++)
        tmp[i] = stuck[i];
    if (dep == n) {
        cout << ans << endl;
        return;
    }
    if (tot) {
        dfs(now, tot - 1, dep + 1, ans + tmp[tot] + ' ', tmp);
    }
    if (now <= n) {
        tmp[tot + 1] = a[now];
        dfs(now + 1, tot + 1, dep, ans, tmp);
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    b[1] = a[1];
    dfs(1, 0, 0, "", b);
}