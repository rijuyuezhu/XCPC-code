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
const int P = 998244353;
ll l, r;
ll calc(ll x) {
    ll ans = 0;
    for(int i = 1, j; i <= x; i = j + 1) {
        j = x / (x / i);
        ans = (ans + (j - i + 1) * (x / i) % P) % P;
    }
    return ans;
}
int main() {
    l = read(), r = read();
    printf("%d", ((calc(r) - calc(l-1)) % P + P) % P);
    return 0;
}
