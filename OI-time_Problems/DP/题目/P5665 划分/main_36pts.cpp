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
const int MAXN = 405;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, ty;
ll a[MAXN], sum[MAXN], f[MAXN][MAXN];
ll sqr(ll x) {
    return x * x;
}
int main() {
    n = read(), ty = read();
    for(int i = 1; i <= n; i++) {
        a[i] = read();
        sum[i] = sum[i-1] + a[i];
    }
    memset(f, 0x3f, sizeof f);
    for(int i = 1; i <= n; i++) {
        f[i][0] = sqr(sum[i]);
        for(int j = 1; j < i; j++)
            for(int k = 0; k < j; k++)
                if(sum[i] - sum[j] >= sum[j] - sum[k])
                    f[i][j] = min(f[i][j], f[j][k] + sqr(sum[i] - sum[j]));
    }
    ll ans = INF;
    for(int i = 0; i <= n; i++) 
        ans = min(ans, f[n][i]);
    printf("%lld\n", ans);
    return 0;
}