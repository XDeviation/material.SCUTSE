#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
int tree[1000];
void preorder(int node) {
    cout << tree[node] << ' ';
    if (tree[node * 2]) preorder(node * 2);
    if (tree[node * 2 + 1]) preorder(node * 2 + 1);
}
void in_order(int node) {
    if (tree[node * 2]) in_order(node * 2);
    cout << tree[node] << ' ';
    if (tree[node * 2 + 1]) in_order(node * 2 + 1);
}
void post_order(int node) {
    if (tree[node * 2]) post_order(node * 2);
    if (tree[node * 2 + 1]) post_order(node * 2 + 1);
    cout << tree[node] << ' ';
}
void level() {
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        cout << tree[q.front()] << ' ';
        if (tree[q.front() * 2]) q.push(q.front() * 2);
        if (tree[q.front() * 2 + 1]) q.push(q.front() * 2 + 1);
        q.pop();
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> tree[i];
    preorder(1);
    cout << endl;
    in_order(1);
    cout << endl;
    post_order(1);
    cout << endl;
    level();
    cout << endl;
    return 0;
}
/*
7
1 2 3 4 5 6 7

1 2 4 5 3 6 7
4 2 5 1 6 3 7
4 5 2 6 7 3 1
1 2 3 4 5 6 7
*/