#include <iostream>
using namespace std;

struct Node {
    int r;
    int c;
    int d;
};

struct Triad {
    int rows;
    int cols;
    int nums;
    Node data[100];
};

static void create_matrix(Triad &t, int A[4][4]) {

    t.rows = 4;
    t.cols = 4;
    t.nums = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (A[i][j] != 0) {
                t.data[t.nums].r = i;
                t.data[t.nums].c = j;
                t.data[t.nums].d = A[i][j];
                t.nums++;
            }
        }
    }
}

static void show(Triad t) {
    for (int i = 0; i < t.nums; i++)
        cout << t.data[i].r << ' ' << t.data[i].c << ' ' << t.data[i].d << '\n';
    cout << '\n';
}

static int get_value(Triad t, int i, int j) {
    int k = 0;

    while (k < t.nums && (t.data[k].r != i || t.data[k].c != j))
        k++;
    if (k < t.nums)
        return t.data[k].d;
    else
        return 0;
}

static bool multi(Triad a, Triad b, Triad &c) {
    int i;
    int j;
    int k;
    int p = 0;
    int s;

    if (a.cols != b.rows) return false;
    for (i = 0; i < a.rows; i++) {
        for (j = 0; j < b.cols; j++) {
            s = 0;
            for (k = 0; k < a.cols; k++) {
                s = s + get_value(a, i, k) * get_value(b, k, j);
            }
            if (s != 0) {
                c.data[p].r = i;
                c.data[p].c = j;
                c.data[p].d = s;
                p++;
            }
        }
    }

    c.rows = a.rows;
    c.cols = b.cols;
    c.nums = p;

    return true;
}

int main(void) {
    int a1[4][4];
    int b1[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> a1[i][j];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> b1[i][j];
    Triad a, b, c;

    create_matrix(a, a1);
    create_matrix(b, b1);
    show(a);
    show(b);

    multi(a, b, c);
    show(c);

    return 0;
}