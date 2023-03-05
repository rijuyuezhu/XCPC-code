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
const int MAXN = 1 << 20, G = 3, P = 998244353, invG = 332748118;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a - b + P : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll qpow(ll a, ll n) {ll ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int tr[MAXN];
void tpre(int lim) {
	for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void NTT(ll* f, int lim, int fl) {
	for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1) {
		ll g0 = qpow(fl ? G : invG, (P-1) / l);
		for(int i = 0; i < lim; i += l) {
			ll gn = 1;
			for(int j = i; j < i+k; j++, gn = mul(gn, g0)) {
				ll tt = mul(gn, f[j+k]);
				f[j+k] = mns(f[j], tt);
				f[j] = pls(f[j], tt);
			}
		}
	}
	if(!fl) {
		ll in = qpow(lim, P-2);
		for(int i = 0; i < lim; i++) f[i] = mul(f[i], in);
	}
}
void Mul(ll* f, ll* g, ll* h, int len) {
	static ll a[MAXN], b[MAXN];
	int lim = 1; for(; lim < len + len; lim <<= 1);
	for(int i = 0; i < len; i++) a[i] = f[i], b[i] = g[i];
	for(int i = len; i < lim; i++) a[i] = b[i] = 0;
	tpre(lim); NTT(a, lim, 1); NTT(b, lim, 1);
	for(int i = 0; i < lim; i++) h[i] = mul(a[i], b[i]);
	NTT(h, lim, 0);
	for(int i = len; i < lim; i++) h[i] = 0;
}
void Inv(ll* f, ll* g, int len) {
	static ll a[MAXN];
	if(len == 1) {g[0] = qpow(f[0], P-2); return;}
	Inv(f, g, (len + 1) >> 1);
	int lim = 1; for(; lim < len + len; lim <<= 1);
	for(int i = 0; i < len; i++) a[i] = f[i];
	for(int i = len; i < lim; i++) a[i] = 0;
	tpre(lim); NTT(a, lim, 1); NTT(g, lim, 1);
	for(int i = 0; i < lim; i++) g[i] = (2 - g[i] * a[i] % P + P) % P * g[i] % P;
	NTT(g, lim, 0);
	for(int i = len; i < lim; i++) g[i] = 0;
}
void Deriv(ll* f, ll* g, int len) {
	for(int i = 1; i < len; i++) g[i-1] = f[i] * i % P;
	g[len-1] = 0;
}
void Integ(ll* f, ll* g, int len) {
	for(int i = 1; i < len; i++) g[i] = f[i-1] * qpow(i, P-2) % P;
	g[0] = 0;
}
void Ln(ll* f, ll* g, int len) {
	static ll a[MAXN], b[MAXN];
	memset(a, 0x00, sizeof a); memset(b, 0x00, sizeof b);
	Deriv(f, a, len); Inv(f, b, len);
	Mul(a, b, a, len);
	Integ(a, g, len);
}
int n;
ll f[MAXN], g[MAXN];
int main() {
	n = read();
	for(int i = 0; i < n; i++) f[i] = read();
	Ln(f, g, n);
	for(int i = 0; i < n; i++) printf("%lld ", g[i]);
	printf("\n");
	return 0;
}
