#include <bits/stdc++.h>
using namespace std;
struct Node {
    int val;
    double coef;
    struct Node *nxt;
};
int a[100];
int main() {
    int n;
    cin >> n;
    struct Node *addnode, *ahead, *bhead, *tmp, **p;
    ahead = new struct Node;
    bhead = new struct Node;
    addnode = new struct Node;
    tmp = ahead;
    for (int i = 1; i <= n; i++) {
        cin >> tmp->val;
        a[i] = tmp->val;
        tmp->nxt = new struct Node;
        if (i == n) tmp->nxt = NULL;
        tmp = tmp->nxt;
    }
    cin >> addnode->val;
    tmp = ahead;
    int now = 1;
    while (addnode->val >= a[now]) {
        now++;
    }
    while (addnode->val >= tmp->nxt->val) {
        tmp = tmp->nxt;
    }
    addnode->nxt = tmp->nxt;
    tmp->nxt = addnode;
    for (int i = n + 1; i > now; i--) {
        a[i] = a[i - 1];
    }
    a[now] = addnode->val;
    for (int i = 1; i <= n + 1; i++)
        cout << a[i] << ' ';
    cout << endl << ahead->val << ' ';
    while (ahead->nxt != NULL) {
        ahead = ahead->nxt;
        cout << ahead->val << ' ';
    }
}
/*
5
1 3 5 7 9
6

1 3 5 6 7 9
1 3 5 6 7 9
*/