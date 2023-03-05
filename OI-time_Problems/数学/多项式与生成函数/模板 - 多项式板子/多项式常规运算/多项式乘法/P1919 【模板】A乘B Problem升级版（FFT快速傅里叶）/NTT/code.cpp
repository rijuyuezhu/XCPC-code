#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e6 + 5;
ll P = 998244353, G = 3, invG = 332748118;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll qpow(ll a, ll n) {
	ll ret = 1;
	for(; n; n >>= 1, a = mul(a, a))
		if(n & 1) ret = mul(ret, a);
	return ret;
}
void In(ll* f, int& n) {
	static char buff[MAXN];
	scanf("%s", buff); n = strlen(buff);
	for(int i = 0; i < n; i++) f[i] = buff[n-i-1] - '0';
}

int tr[MAXN];
void NTT(ll* f, int n, int fl) {
	for(int i = 0; i < n; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, hl = 1; l <= n; l <<= 1, hl <<= 1) {
		ll g0 = qpow(fl == 1 ? G : invG, (P-1) / l);
		for(int i = 0; i < n; i += l) {
			ll gn = 1;
			for(int j = i; j < i + hl; j++, gn = mul(gn, g0)) {
				ll tt = mul(gn, f[j+hl]);
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
ll f[MAXN], g[MAXN];
int n, m, d;
int main() {
	In(f, n); In(g, m);
	for(d = 1; d <= n+m; d <<= 1);
	for(int i = 0; i < d; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (d >> 1) : 0);
	NTT(f, d, 1); NTT(g, d, 1);
	for(int i = 0; i < d; i++) f[i] = mul(f[i], g[i]);
	NTT(f, d, -1);
	for(int i = 0; i < d; i++)
		f[i+1] += f[i] / 10, f[i] %= 10;
	int len = d+1;
	while(len > 1 && f[len-1] == 0) len--;
	for(int i = len - 1; i >= 0; i--) printf("%lld", f[i]);
	printf("\n");
	return 0;
}
