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
const int MAXN = 100005;
ll n, a[MAXN], b[MAXN];

void exgcd(ll a, ll b, ll& x, ll& y) {
    if(!b) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= (a / b) * x;
}
ll CRT() {
    ll M = 1, ans = 0;
    for(int i = 1; i <= n; i++) M *= a[i];
    for(int i = 1; i <= n; i++) {
        ll Mi = M / a[i], x, y;
        exgcd(Mi, a[i], x, y);
        ans = (ans + b[i] * Mi * x) % M;
    }
    return (ans % M + M) % M;
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) {
        a[i] = read(), b[i] = read();
    }
    printf("%ld\n", CRT());
    return 0;
}