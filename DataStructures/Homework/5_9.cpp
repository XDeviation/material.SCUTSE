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

static bool add(Triad a, Triad b, Triad &c) {
    int i = 0;
    int j = 0;
    int k = 0;
    int v;

    if (a.rows != b.rows || a.cols != b.cols) return false;

    c.rows = a.rows;
    c.cols = a.cols;
    while (i < a.nums && j < b.nums) {
        if (a.data[i].r == b.data[j].r) {
            if (a.data[i].c < b.data[j].c) {

                c.data[k].r = a.data[i].r;
                c.data[k].c = a.data[i].c;
                c.data[k].d = a.data[i].d;
                k++;
                i++;
            } else if (a.data[i].c > b.data[j].c) {

                c.data[k].r = b.data[j].r;
                c.data[k].c = b.data[j].c;
                c.data[k].d = b.data[j].d;
                k++;
                j++;
            } else {
                v = a.data[i].d + b.data[j].d;
                if (v != 0) {
                    c.data[k].r = a.data[i].r;
                    c.data[k].c = a.data[i].c;
                    c.data[k].d = v;
                    k++;
                }
                i++;
                j++;
            }
        } else if (a.data[i].r < b.data[j].r) {

            c.data[k].r = a.data[i].r;
            c.data[k].c = a.data[i].c;
            c.data[k].d = a.data[i].d;
            k++;
            i++;
        } else {

            c.data[k].r = b.data[j].r;
            c.data[k].c = b.data[j].c;
            c.data[k].d = b.data[j].d;
            k++;
            j++;
        }
        c.nums = k;
    }

    return true;
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

    add(a, b, c);
    show(c);

    return 0;
}