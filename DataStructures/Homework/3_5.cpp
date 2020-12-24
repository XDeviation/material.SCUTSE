#include <bits/stdc++.h>
using namespace std;
struct Node {
    int val;
    double coef;
    struct Node *nxt;
};
int a[100];
int main() {
    struct Node *addnode, *head, *tmp, **p;
    head = new struct Node;
    addnode = new struct Node;
    tmp = head;
    cout << "Please input the element, if you want to ending, input 'exit'\n";
    string s;
    cin >> s;
    while (s != "exit") {
        tmp->val = stoi(s);
        tmp->nxt = new struct Node;
        cin >> s;
        if (s != "exit")
            tmp = tmp->nxt;
        else
            tmp->nxt = NULL;
    }
    cout << "Your input linked list is:\n";
    while (head != NULL) {
        cout << head->val << ' ';
        head = head->nxt;
    }
}
/*
1
2
34
45
56
exit

Your input linked list is:
1 2 34 45 56
*/