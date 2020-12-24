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

    int High() {
        queue<pair<node *, int>> q;
        int ret = 0;
        q.push({root, 1});
        while (!q.empty()) {
            pair<node *, int> tmp = q.front();
            q.pop();
            ret = tmp.second;
            if (tmp.first->left) q.push({tmp.first->left, tmp.second + 1});
            if (tmp.first->right) q.push({tmp.first->right, tmp.second + 1});
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
    cout << tree.High();
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

3
*/