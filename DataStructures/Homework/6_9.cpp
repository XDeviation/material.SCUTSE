#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

class node {
  public:
    int val;
    node *left, *right;
    node(int _val)
        : val(_val)
        , left(nullptr)
        , right(nullptr) {
    }
};

class Binaryintree {
  public:
    node *root;

    Binaryintree(int n, int rt, int son[][2])
        : root(nullptr) {
        queue<node *> q;
        q.push(root = new node(rt));
        while (!q.empty()) {
            node *tmp = q.front();
            q.pop();
            if (son[tmp->val][0])
                q.push(tmp->left = new node(son[tmp->val][0]));
            if (son[tmp->val][1])
                q.push(tmp->right = new node(son[tmp->val][1]));
        }
    }

    bool isHeightBalance() {
        bool ret = true;
        heightBalance(root, ret);
        return ret;
    }

    int heightBalance(node *&p, bool &isBalance) {
        if (!isBalance) return 0;
        int l = (p->left ? heightBalance(p->left, isBalance) : 0);
        int r = (p->right ? heightBalance(p->right, isBalance) : 0);
        isBalance &= (l == r || (l + 1) == r || (r + 1) == l);
        return max(l, r) + 1;
    }
};

int son[100][2];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> son[i][0] >> son[i][1];

    Binaryintree tree(n, 1, son);
    cout << tree.isHeightBalance();
}

/*
7
2 3
4 5
6 7
0 0
0 0
0 0
0 0

1
*/