#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

constexpr int MAXN = 1e6 + 5;
int n, m, q;
int r[MAXN], c[MAXN];
int remain_r, remain_c;
int t[MAXN];
char ob[MAXN], op[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    remain_r = n;
    remain_c = m;
    for (int i = 1; i <= q; i++) {
        string tmp;
        cin >> tmp;
        ob[i] = tmp[0];
        cin >> t[i];
        cin >> tmp;
        op[i] = tmp[1];
    }
    ll ans = 0;
    for (int i = q; i >= 1; i--) {
        if (ob[i] == 'r') {
            if (!r[t[i]]) {
                r[t[i]] = 1;
                if (op[i] == 'n')
                    ans += remain_c;
                remain_r--;
            }
        } else {
            if (!c[t[i]]) {
                c[t[i]] = 1;
                if (op[i] == 'n')
                    ans += remain_r;
                remain_c--;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
