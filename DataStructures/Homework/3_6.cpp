#include <bits/stdc++.h>
using namespace std;
struct Node {
    int val;
    struct Node *nxt;
} * ps;
void LinkReverse(struct Node *head) {
    if (head->nxt->nxt)
        LinkReverse(head->nxt);
    else
        ps = head->nxt;
    head->nxt->nxt = head;
}

int main() {
    struct Node *head, *tmp, **p;

    tmp = head = new struct Node;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> tmp->val;
        tmp->nxt = new struct Node;
        if (i == n) tmp->nxt = NULL;
        tmp = tmp->nxt;
    }

    ps = head;
    do {
        cout << ps->val << ' ';
    } while (ps = ps->nxt);
    cout << endl;

    if (head->nxt) {
        LinkReverse(head);
        head->nxt = NULL;
        head = ps;
    }
    ps = head;
    do {
        cout << head->val << ' ';
    } while (head = head->nxt);
    cout << endl;
}
/*
4
1 2 3 4

1 2 3 4
4 3 2 1
*/