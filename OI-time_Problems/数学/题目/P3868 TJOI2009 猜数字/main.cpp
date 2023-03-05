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
const int MAXK = 15;
int k;
ll a[MAXK], b[MAXK];

void exgcd(ll a, ll b, ll& x, ll& y) {
    if(!b) {x = 1, y = 0;}
    else {exgcd(b, a % b, y, x); y -= (a / b) * x;}
}
ll ksc(ll a, ll b, ll mod) {// be sure that b >= 0
    ll res = 0;
    while(b) {
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}
ll CRT() {
    ll M = 1, x, y, ans = 0;
    for(int i = 1; i <= k; i++) M *= b[i];
    for(int i = 1; i <= k; i++) {
        ll Mi = M / b[i];
        exgcd(Mi, b[i], x, y);
        a[i] = (a[i] % b[i] + b[i]) % b[i];
        x = (x % b[i] + b[i]) % b[i];
        ans = (ans + ksc(ksc(a[i], Mi, M), x, M)) % M;
    }
    ans = (ans % M + M) % M;
    return ans;
}
int main() {
    k = read();
    for(int i = 1; i <= k; i++) a[i] = read();
    for(int i = 1; i <= k; i++) b[i] = read();
    printf("%lld\n", CRT());
    return 0;
}