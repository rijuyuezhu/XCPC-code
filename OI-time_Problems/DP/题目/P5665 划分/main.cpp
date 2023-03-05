// https://www.luogu.com.cn/problem/P5665
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
const int MAXN = 5e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, ty;
ll a[MAXN], sum[MAXN];
int g[MAXN], que[MAXN], hd, tl;
ll calc(int x) {
    return 2 * sum[x] - sum[g[x]];
}
ll sqr(ll x) {
    return x * x;
}
int main() {
    n = read(), ty = read();
    for(int i = 1; i <= n; i++) {
        a[i] = read();
        sum[i] = sum[i-1] + a[i];
    }
    hd = 1; tl = 0; que[++tl] = 0;
    for(int i = 1; i <= n; i++) {
        while(hd < tl && calc(que[hd+1]) <= sum[i]) hd++;
        g[i] = que[hd];
        while(hd <= tl && calc(que[tl]) >= calc(i)) tl--;
        que[++tl] = i;  
    }
    ll ans = 0;
    for(int now = n; now; now = g[now]) {
        ans += sqr(sum[now] - sum[g[now]]);
    }
    printf("%lld\n", ans);
    return 0;
}