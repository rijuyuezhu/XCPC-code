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
ll x, y, m, n, L, g;
ll gcd(ll a, ll b) {
    if(!b) return a;
    return gcd(b, a % b);
}
void exgcd(ll a, ll b, ll& x, ll& y){
    if(!b) {x = 1; y = 0;}
    else {exgcd(b, a % b, y, x); y -= (a / b) * x;}
}
int main() {
    x = read(), y = read(), m = read(), n = read(), L = read();
    ll A = n - m, B = L, C = x - y;
    if(A < 0) A = -A, C = -C;
    ll g = gcd(A, B);
    if(C % g != 0) printf("Impossible\n");
    else {
        A /= g, B /= g, C /= g;
        ll x0, y0;
        exgcd(A, B, x0, y0);
        x0 *= C;
        printf("%lld\n", (x0 % B + B) % B);
    }

    return 0;
}