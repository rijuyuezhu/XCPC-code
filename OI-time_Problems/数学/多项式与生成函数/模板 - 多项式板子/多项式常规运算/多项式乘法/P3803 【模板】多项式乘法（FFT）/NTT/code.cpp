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
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e6 + 5;
const int P = 998244353, G = 3, invG = 332748118;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
int n, m, d, id[MAXN];
ll f[MAXN], g[MAXN];
ll qpow(ll a, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, a = mul(a, a)) 
		if(n & 1) ret = mul(ret, a);
	return ret;
}
void NTT(ll* f, int n, int fl) {
	for(int i = 0; i < n; i++) if(i < id[i]) swap(f[i], f[id[i]]);
	for(int l = 2, hl = 1; l <= n; l <<= 1, hl <<= 1) {
		ll g0 = qpow(fl == 1 ? G : invG, (P-1) / l);
		for(int i = 0; i < n; i += l) {
			ll gn = 1;
			for(int j = i; j < i + hl; j++, gn = mul(gn, g0)) {
				ll tt = mul(f[j+hl], gn);
				f[j+hl] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
		}
	}
	if(fl == -1) {
		ll invn = qpow(n, P-2);
		for(int i = 0; i < n; i++) f[i] = mul(f[i], invn);
	}
}
int main() {
	n = read(); m = read();
	for(int i = 0; i <= n; i++) f[i] = read();
	for(int i = 0; i <= m; i++) g[i] = read();
	for(d = 1; d <= n+m; d <<= 1);
	for(int i = 0; i < d; i++) id[i] = (id[i >> 1] >> 1) | ((i & 1) ? (d >> 1) : 0);
	NTT(f, d, 1); NTT(g, d, 1);
	for(int i = 0; i < d; i++) f[i] = mul(f[i], g[i]);
	NTT(f, d, -1);
	for(int i = 0; i <= n+m; i++) printf("%lld ", f[i]);
	printf("\n");
	return 0;
}
