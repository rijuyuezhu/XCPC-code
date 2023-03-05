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
ll CRT() {
    ll M = 1, x, y, ans = 0;
    for(int i = 1; i <= k; i++) M *= b[i];
    for(int i = 1; i <= k; i++) {
        ll Mi = M / b[i];
        exgcd(Mi, b[i], x, y);
        x = (x % b[i] + b[i]) % b[i];
        a[i] = (a[i] % b[i] + b[i]) % b[i];
        ans = (ans + a[i] * x % M * Mi % M) % M;
    }
    ans = (ans % M + M) % M;
    return ans;
}
int main() {
    k = read();
    for(int i = 1; i <= k; i++) a[i] = read();
    for(int i = 1; i <= k; i++) b[i] = read();
    printf("%d\n", CRT());
    return 0;
}