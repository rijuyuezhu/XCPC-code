#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
using ll = long long;
constexpr int MAXN = 1005;
int n, len, nxt[MAXN];
string t, buff;
void work() {
    cin >> n >> t;
    len = t.length();
    t = ' ' + t;
    nxt[0] = nxt[1] = 0;
    buff = string();
    int j = 0;
    for (int i = 2; i <= len; i++) {
        while(j && t[j+1] != t[i])
            j = nxt[j];
        if (t[j+1] == t[i])
            j++;
        nxt[i] = j;
    }
    j = nxt[len];
    for (int i = 1; i <= n; i++) {
        char c = (int(t[j+1] - '0') ^ 1) + '0';
        while (j && t[j+1] != c)
            j = nxt[j];
        if (t[j+1] == c)
            j++;
        buff.push_back(c);
    }
    bool flag = 1;
    for (int i = 1; i <= len; i++) {
        while (j && t[j+1] != t[i])
            j = nxt[j];
        if (t[j+1] == t[i])
            j++;
        if (j == len) {
            if (i != len)
                flag = 0;
            break;
        }
    }
    if (flag)
        cout << buff << '\n';
    else 
        cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) 
        work();
    return 0;
}
