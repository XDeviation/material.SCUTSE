#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

vector<int> mp[100], dfstree[100];
bool check[100];
pair<int, int> checktime[100];
void maketree(int x, int y) {
    mp[x].push_back(y);
}
void makeans(int x, int y) {
    dfstree[x].push_back(y);
}
int nowtime = 1;
void dfs(int now) {
    checktime[now].first = nowtime;
    nowtime++;

    for (auto i : mp[now])
        if (!check[i]) {
            check[i] = true;
            makeans(now, i);
            dfs(i);
        }

    checktime[now].second = nowtime;
    nowtime++;
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
    for (int i = 1; i <= n; i++) {
        cout << i << ' ' << checktime[i].first << '&' << checktime[i].second
             << '\n';
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
1 1&12
2 2&5
3 7&8
4 3&4
5 6&11
6 9&10
*/