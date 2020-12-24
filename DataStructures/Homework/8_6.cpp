#include <iostream>
#include <queue>
using namespace std;
class Node {
  public:
    Node(int _tag, string _name, Node *_next, Node *_son, int _val) {
        tag = _tag, name = _name, next = _next, son = _son, val = _val, dep = 0;
    }
    int tag; // 0 / 1
    string name;
    Node *next;
    Node *son;
    int val;
    int dep;
};
int main() {

    Node *a4 = new Node(0, "f", NULL, NULL, 4);
    Node *a4f = new Node(1, "e", NULL, a4, 0);
    Node *a3 = new Node(0, "d", a4f, NULL, 3);
    Node *a2 = new Node(0, "c", a3, NULL, 2);
    Node *a2f = new Node(1, "b", NULL, a2, 0);
    Node *a1 = new Node(0, "a", a2f, NULL, 1);
    Node *root = new Node(1, "root", NULL, a1, 0);
    queue<Node *> q;
    string finds = "e";
    q.push(root);
    while (!q.empty()) {
        Node *now = q.front();
        q.pop();
        if (now->name == finds) cout << "dep = " << now->dep << '\n';
        Node *add = now;
        while (add->next != NULL) {
            if (add->next->dep == 0) q.push(add->next);
            add->next->dep = add->dep;
            add = add->next;
        }
        if (now->son != NULL) {
            now->son->dep = now->dep + 1;
            q.push(now->son);
        }
    }
    return 0;
}
/*
(1,(2,3,(4)))

dep = 2
*/