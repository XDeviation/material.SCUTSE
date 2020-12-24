#include <bits/stdc++.h>

using namespace std;
const int N = 1e+7 + 1;
const double Pi = acos(-1);
int n, m, rev[N];
complex<double> F[N], G[N], H[N];

int invert(int n) {
    int bit = 1;
    while ((1 << bit) < n)
        bit++;
    return (1 << bit);
}
int getint() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = (x << 1) + (x << 3) + c - '0', c = getchar();
    return x * f;
}
void FFT(complex<double> *A, int n, int inv) {
    int bit = 1;
    while ((1 << bit) < n)
        bit++;
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i]) swap(A[i], A[rev[i]]);
    }
    for (int mid = 1; mid < n; mid <<= 1) {
        complex<double> temp(cos(Pi / mid), inv * sin(Pi / mid));
        for (int i = 0; i < n; i += mid << 1) {
            complex<double> omega(1, 0);
            for (int j = 0; j < mid; j++, omega *= temp) {
                complex<double> x = A[i + j], y = omega * A[i + j + mid];
                A[i + j] = x + y;
                A[i + j + mid] = x - y;
            }
        }
    }
}
int main() {
    cin >> n;
    for (int i = 0; i <= n; i++)
        F[i].real(getint());
    for (int i = 0; i <= n; i++)
        G[i].real(getint());
    FFT(F, invert(n * 2), 1);
    FFT(G, invert(n * 2), 1);
    for (int i = 0; i <= invert(n * 2); i++)
        H[i] = F[i] * G[i];
    FFT(H, invert(n * 2), -1);
    for (int i = 0; i <= n * 2; i++)
        cout << (int) (H[i].real() / invert(n * 2) + 0.5) << ' ';
    return 0;
}
/*
3
1 2 3 45
1 2 3 4

1 4 10 61 107 147 180
*/