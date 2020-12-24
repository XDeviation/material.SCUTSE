#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

vector<int> mp[100], dfstree[100];
bool check[100];
int pai[100];
void maketree(int x, int y) {
    mp[x].push_back(y);
}
void makeans(int x, int y) {
    dfstree[x].push_back(y);
}
int nowtime = 1;
void dfs(int now) {
    pai[nowtime++] = now;

    for (auto i : mp[now])
        if (!check[i]) {
            check[i] = true;
            makeans(now, i);
            dfs(i);
        }
    pai[nowtime++] = now;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        maketree(x, y);
    }
    check[1] = true;
    dfs(1);
    for (int i = 1; i <= n; i++) {
        for (auto j : dfstree[i]) {
            cout << i << "->" << j << '\n';
        }
    }
    for (int i = 1; i <= n; i++)
        check[i] = false;
    for (int i = 1; i <= 2 * n; i++) {
        if (check[pai[i]])
            cout << ' ' << pai[i] << " )";
        else {
            cout << " ( " << pai[i];
            check[pai[i]] = true;
        }
    }
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
 ( 1 ( 2 ( 4 4 ) 2 ) ( 5 ( 3 3 ) ( 6 6 ) 5 ) 1 )
*/