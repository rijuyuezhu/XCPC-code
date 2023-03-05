//https://www.luogu.com.cn/problem/P2261
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
ll n, k;
ll ans;
int main() {
    n = read(), k = read();
    ans = n * k;
    for(ll l = 1, r; l <= n; l = r + 1) {
        r = k / l ? min(k / (k / l), n) : n;
        ans -= (k / l) * (l + r) * (r - l + 1) / 2;
    }
    printf("%lld\n", ans);
    return 0;
}