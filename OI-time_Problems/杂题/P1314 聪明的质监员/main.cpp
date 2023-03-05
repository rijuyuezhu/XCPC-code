#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 2e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
ll n, m, s;
ll w[MAXN], v[MAXN];
ll rl[MAXN], rr[MAXN];
ll wmn, wmx;
ll snum[MAXN], sv[MAXN];
ll res;
bool check(ll W) {
    for(int i = 1; i <= n; i++) {
        snum[i] = snum[i-1] + (w[i] >= W);
        sv[i] = sv[i-1] + v[i] * (w[i] >= W);
    }
    ll y = 0;
    for(int i = 1; i <= m; i++)
        y += (sv[rr[i]] - sv[rl[i]-1]) * (snum[rr[i]] - snum[rl[i]-1]);
    res = labs(y - s);
    if(y >= s) return false;//too small W
    return true;
}
int main() {
    n = read(), m = read(), s = read();
    for(int i = 1; i <= n; i++) w[i] = read(), v[i] = read();
    for(int i = 1; i <= m; i++) rl[i] = read(), rr[i] = read();
    wmn = INF, wmx = 0;
    for(int i = 1; i <= n; i++) wmn = min(wmn, w[i]), wmx = max(wmx,w[i]);
    ll l = wmn, r = wmx+1, ans = INF;
    while(l <= r) {
        ll m = (l + r) >> 1;
        if(check(m)) r = m - 1;
        else l = m + 1;
        ans = min(ans, res);
    }
    printf("%lld\n", ans);
    return 0;
}
