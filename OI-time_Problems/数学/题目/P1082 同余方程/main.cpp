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
ll a, b;
void exgcd(ll a, ll b, ll& x, ll& y) {
    if(!b) {x = 1; y = 0;}
    else exgcd(b, a % b, y, x), y -= (a / b) * x;
}

int main() {
    a = read(), b = read();
    ll x, y;
    exgcd(a, b, x, y);
    printf("%lld\n", (x % b + b) % b);
    return 0;
}