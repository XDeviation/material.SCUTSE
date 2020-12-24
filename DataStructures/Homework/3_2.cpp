#include <bits/stdc++.h>
using namespace std;
struct Node {
    int val;
    double coef;
    struct Node *nxt;
};
int a[100], b[100], c[100];
int main() {
    int n, m;
    cin >> n >> m;
    struct Node *ahead, *bhead, *tmp, **p, *ans;
    ahead = new struct Node;
    bhead = new struct Node;
    ans = new struct Node;
    tmp = ahead;
    for (int i = 1; i <= n; i++) {
        cin >> tmp->val;
        a[i] = tmp->val;
        tmp->nxt = new struct Node;
        if (i == n) tmp->nxt = NULL;
        tmp = tmp->nxt;
    }

    tmp = bhead;
    for (int i = 1; i <= m; i++) {
        cin >> tmp->val;
        b[i] = tmp->val;
        tmp->nxt = new struct Node;
        if (i == m) tmp->nxt = NULL;
        tmp = tmp->nxt;
    }
    int l = 1, r = 1;
    int tot = 0;
    while (tot < n + m) {
        if (l > n) {
            c[++tot] = b[r];
            r++;
        } else if (r > m) {
            c[++tot] = a[l];
            l++;
        } else if (a[l] < b[r]) {
            c[++tot] = a[l];
            l++;
        } else {
            c[++tot] = b[r];
            r++;
        }
    }
    tmp = ans;
    while (ahead != NULL || bhead != NULL) {
        if (ahead == NULL) {
            ans->nxt = new struct Node;
            ans = ans->nxt;
            ans->val = bhead->val;
            bhead = bhead->nxt;
        } else if (bhead == NULL) {
            ans->nxt = new struct Node;
            ans = ans->nxt;
            ans->val = ahead->val;
            ahead = ahead->nxt;
        } else if (ahead->val < bhead->val) {
            ans->nxt = new struct Node;
            ans = ans->nxt;
            ans->val = ahead->val;
            ahead = ahead->nxt;
        } else {
            ans->nxt = new struct Node;
            ans = ans->nxt;
            ans->val = bhead->val;
            bhead = bhead->nxt;
        }
    }
    tmp = tmp->nxt;
    for (int i = 1; i <= tot; i++)
        cout << c[i] << ' ';
    cout << endl;
    while (tmp != NULL) {
        cout << tmp->val << ' ';
        tmp = tmp->nxt;
    }
}
/*
4 3
1 3 5 7
2 4 6

1 2 3 4 5 6 7
1 2 3 4 5 6 7
*/