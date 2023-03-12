#include <iostream>
#include <algorithm>
using namespace std;
constexpr int MAXN = 1e6 + 5;
int n;
int deg[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
    }
    int flag = 0, ans = 0;
    for(int i = 1; i <= n && !flag; i++) {
        if(deg[i] > 3)
            flag = 1;
        else if(deg[i] <= 2)
            ++ans;
    }
    if(flag)
        cout << 0 << '\n';
    else
        cout << ans << '\n';
    return 0;
}
