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

    void leafPath(node *&p, vector<int> &vec) {
        vec.push_back(p->val);
        if (p->left || p->right) {
            if (p->left) leafPath(p->left, vec);
            if (p->right) leafPath(p->right, vec);
        } else {
            for (auto &i : vec)
                cout << i << ' ';
            cout << endl;
        }
        vec.pop_back();
    }
};

int son[100][2];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> son[i][0] >> son[i][1];

    Binaryintree tree(n, 1, son);

    vector<int> ans;
    tree.leafPath(tree.root, ans);
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

1 2 4
1 2 5
1 3 6
1 3 7
*/