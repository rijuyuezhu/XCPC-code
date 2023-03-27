#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
constexpr int MAXN = 22;
int n;
ll a[MAXN], x, ans;

bool cmp(ll a, ll b) {
    return a > b;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> x;
    sort(a + 1, a + 1 + n, cmp);
    int U = 1 << (n-1);
    for(int i = 0; i < U; i++) {
        ll ret = x;
        for(int j = 1; j <= n-1; j++)
            if((i >> (j-1)) & 1)
                ret %= a[j];
        ret %= a[n];
        ans = max(ans, ret);
    }
    cout << ans << '\n';
    return 0;
}
