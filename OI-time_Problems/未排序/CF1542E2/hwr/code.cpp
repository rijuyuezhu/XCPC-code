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
const int MAXN = 505, BAS = MAXN * MAXN / 2;
int P = 1;
int MOD(int v) {return v >= P ? v : v - P;}
struct mint {
	int v;
	mint(ll _v = 0) {
		if(_v >= 0 && _v < P)
			v = _v;
		else v = (_v % P + P) % P;
	}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator += (mint& a, mint b) {return a = a + b;}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator -= (mint& a, mint b) {return a = a - b;}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint operator *= (mint& a, mint b) {return a = a * b;}
mint operator - (mint a) {return 0-a;}
mint qpow(mint a, int n) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
mint sqr(mint a) {return a * a;}


int n, sgm[MAXN];
mint f[MAXN], ans, g[2][MAXN * MAXN], G[2][MAXN * MAXN], H[2][MAXN * MAXN];
mint Getg(int n, int d) {
	if(d >= sgm[n]) return 0;
	else if(d < -sgm[n]) return sqr(sgm[n]+1);
	else return g[n & 1][d+BAS];
}
mint GetG(int n, int d) {
	if(!sgm[n]) {
		if(d >= 1) return 0;
		else return d+1;
	}
	if(d >= sgm[n]) return G[n & 1][sgm[n]-1+BAS];
	else if(d < -sgm[n]) return G[n & 1][-sgm[n]+BAS] + g[n & 1][-sgm[n]+BAS] + (-sgm[n] - 1 - d) * sqr(sgm[n]+1);
	else return G[n & 1][d+BAS];
}
mint S(mint n) {return 1ll * n.v * (n.v + 1) / 2;}
mint GetH(int n, int d) {
	if(!sgm[n]) {
		if(d >= 1) return 0;
		else return S(d);
	}
	if(d >= sgm[n]) return H[n & 1][sgm[n]-1+BAS];
	else if(d < -sgm[n]) return G[n & 1][-sgm[n]+BAS] + (-sgm[n]) * g[n & 1][-sgm[n]+BAS] + (S(-sgm[n]-1) - S(d)) * sqr(sgm[n]+1);
	else return H[n & 1][d+BAS];
}
int main() {
	n = read(), P = read();
	for(int i = 0; i <= n; i++) sgm[i] = i * (i-1) / 2;
	for(int i = 0; i < n; i++) {
		int p = i & 1;
		for(int d = -sgm[i]; d < sgm[i]; d++)
			g[p][d+BAS] = i * Getg(i-1,d) + (GetH(i-1,d-1) - GetH(i-1,d-i))
						+ (i-d) * (GetG(i-1,d-1) - GetG(i-1,d-i))
						- (GetH(i-1,d+i-1) - GetH(i-1, d))
						+ (i+d) * (GetG(i-1,d+i-1) - GetG(i-1, d));
		G[p][0+BAS] = H[p][0+BAS] = 0;
		for(int d = 1; d < sgm[i]; d++) {
			G[p][d+BAS] = G[p][d-1+BAS] + g[p][d+BAS];
			H[p][d+BAS] = H[p][d-1+BAS] + d * g[p][d+BAS];
		}
		for(int d = -1; d >= -sgm[i]; d--) {
			G[p][d+BAS] = G[p][d+1+BAS] - g[p][d+1+BAS];
			H[p][d+BAS] = H[p][d+1+BAS] - (d+1) * g[p][d+1+BAS];
		}
		for(int d = 1; d <= i; d++) f[i+1] += (i+1-d) * Getg(i, d);
	}
	mint ans = 0, fac = 1;
	for(int i = 1; i <= n; i++) {
		ans += fac * f[n-i+1];
		fac *= (n-i+1);
	}
	printf("%d\n", ans.v);
	return 0;
}
