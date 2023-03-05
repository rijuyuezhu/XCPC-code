#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ll(ch - '0');
	return x * f;
}
const ll MAXN = 1e9 + 5, MAXR = 1e6 + 5;
const ll P = 1e9 + 7;
ll n;
ll pr[MAXR], ip[MAXR], tot, f[MAXR], inv6;
ll ksm(ll a, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, a = a * a % P) 
		if(n & 1) ret = ret * a % P;
	return ret;
}
void init() {
	inv6 = ksm(6, P-2);
	ip[1] = 1; f[1] = 1;
	for(ll i = 2; i < MAXR; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			f[i] = i-1;
		}
		for(ll j = 1; j <= tot && 1ll * i * pr[j] < MAXR; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j]) {
				f[i * pr[j]] = f[i] * (pr[j] - 1) % P;
			} else {
				f[i * pr[j]] = f[i] * pr[j] % P;
				break;
			}
		}
	}
	for(ll i = 1; i < MAXR; i++) 
		f[i] = (f[i-1] + f[i] * i) % P;
}
ll g(ll x) {
	return x * (x + 1) / 2 % P;
}
ll sf[MAXN / MAXR], vf[MAXN / MAXR];
ll Sf(ll x) {
	if(x < MAXR) return f[x];
	if(vf[n / x]) return sf[n / x];
	vf[n / x] = 1;
	ll ans = 1ll * x * (x + 1) % P * (2 * x + 1) % P * inv6 % P;
	for(ll i = 2, j; i <= x; i = j + 1) {
		j = x / (x / i);
		ans = (ans - (g(j) - g(i-1)) % P * Sf(x / i)) % P;
	}
	return sf[n / x] = (ans % P + P) % P;
}
int main() {
	n = read();
	printf("1\n");
	init();
	printf("%lld\n", Sf(n));
	return 0;
}
