#include <bits/stdc++.h>
using namespace std;
struct Node {
    int val;
    double coef;
    struct Node *nxt;
};
int main() {
    int n;
    cin >> n;
    struct Node *ahead, *bhead, *tmp, **p;
    ahead = new struct Node;
    bhead = new struct Node;
    tmp = ahead;
    for (int i = 1; i <= n; i++) {
        cin >> tmp->val;
        tmp->nxt = new struct Node;
        if (i == n) tmp->nxt = NULL;
        tmp = tmp->nxt;
    }
    tmp = bhead;
    for (int i = 1; i <= n; i++) {
        cin >> tmp->val;
        tmp->nxt = new struct Node;
        if (i == n) tmp->nxt = NULL;
        tmp = tmp->nxt;
    }
    for (int i = 1; i <= n; i++) {
        cout << ahead->val + bhead->val << "X^" << n - i + 1 << ' ';
        ahead = ahead->nxt, bhead = bhead->nxt;
    }
}