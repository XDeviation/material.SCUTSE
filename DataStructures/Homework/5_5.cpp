#include <iostream>
using namespace std;
int a[100], b[100], ans[100];
int loc(int n, int i, int j) {
    return i * n + j;
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i * n + j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> b[i * m + j];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < n; k++)
                ans[i * m + j] += a[i * n + k] * b[k * n + j];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) {
            ans[i * m + j] = 0;
            for (int k = 0; k < n; k++)
                ans[i * m + j] += a[loc(n, i, k)] * b[loc(m, k, j)];
        }
}