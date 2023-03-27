#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;
constexpr int MAXN = 1e5 + 5;
int n, k;
int op[MAXN], opand[MAXN];
int hd;
queue<int> que;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        string s;
        char c;
        int t;
        cin >> s;
        if(s[0] == 'e') {
            cin >> c;
            op[i] = 1;
            opand[i] = c;
        } else {
            cin >> t;
            op[i] = 2;
            opand[i] = t;
        }
    }
    que.push(n);
    hd = 1;
    for(int i = 1; i <= k; i++) {
        if(hd > que.front()) {
            que.pop();
            if(que.empty())
                break;
            hd = 1;
        }
        if(op[hd] == 1)
            cout << (char)opand[hd];
        else
            que.push(opand[hd]);
        hd++;
    }
    cout << '\n';
    return 0;
}

