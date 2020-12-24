#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> mp[100], dfstree[100];
int dep[100];
void maketree(int x, int y) {
    mp[x].push_back(y);
}
void makeans(int x, int y) {
    dfstree[x].push_back(y);
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        maketree(x, y);
    }
    queue<int> q;
    q.push(1);
    dep[1] = 1;
    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        for (auto it : mp[tmp])
            if (!dep[it]) {
                dep[it] = dep[tmp] + 1;
                q.push(it);
                makeans(tmp, it);
            }
    }
    for (int i = 1; i <= n; i++) {
        for (auto j : dfstree[i]) {
            cout << i << "->" << j << '\n';
        }
    }
    for (int i = 1; i <= n; i++)
        cout << i << ':' << dep[i] << '\n';
    return 0;
}
/*
6 7
1 2
2 4
4 1
1 5
5 4
5 3
5 6

1->2
1->5
2->4
5->3
5->6
1:1
2:2
3:3
4:3
5:2
6:3
*/