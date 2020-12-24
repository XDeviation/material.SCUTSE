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

    int Leaf() {
        queue<node *> q;
        int ret = 0;
        q.push(root);
        while (!q.empty()) {
            node *tmp = q.front();
            q.pop();
            if (!tmp->left && !tmp->right) ret++;
            if (tmp->left) q.push(tmp->left);
            if (tmp->right) q.push(tmp->right);
        }
        return ret;
    }
};

int son[100][2];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> son[i][0] >> son[i][1];

    Binaryintree tree(n, 1, son);
    cout << tree.Leaf();
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

4
*/