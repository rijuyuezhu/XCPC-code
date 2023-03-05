#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 21, MAXU = (1 << 20) + 5, Bas = 1 << 20, P = 1e9 + 9;
namespace MINT {
	struct mint {
		int v;
		mint() {}
		mint(int v) : v(v) {}
	};
	int MOD(int v) {return v >= P ? v - P : v;}
	mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
	mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
	mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
	mint operator += (mint& a, mint b) {return a = a + b;}
	mint operator -= (mint& a, mint b) {return a = a - b;}
	mint operator *= (mint& a, mint b) {return a = a * b;}
	mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
} using namespace MINT;
int n, U, cnt1[MAXU];
mint a[MAXN][MAXU], b[MAXN][MAXU], c[MAXN][MAXU];
void fwtor(mint f[], int n) {
	for(int l = 2, k = 1; l <= n; l <<= 1, k <<= 1) 
		for(int i = 0; i < n; i += l)
			for(int j = i; j < i+k; j++)
				f[j+k] += f[j];
}
void ifwtor(mint f[], int n) {
	for(int l = 2, k = 1; l <= n; l <<= 1, k <<= 1) 
		for(int i = 0; i < n; i += l)
			for(int j = i; j < i+k; j++)
				f[j+k] -= f[j];
}
int main() {
	n = read(); U = 1 << n;
	cnt1[0] = 0; for(int i = 1; i < U; i++) cnt1[i] = cnt1[i >> 1] + (i & 1);
	for(int i = 0; i < U; i++) {a[cnt1[i]][i] = read();}
	for(int i = 0; i < U; i++) {b[cnt1[i]][i] = read();}
	for(int i = 0; i <= n; i++) fwtor(a[i], U), fwtor(b[i], U);
	for(int i = 0; i <= n; i++) 
		for(int j = 0; j+i <= n; j++)
			for(int k = 0; k < U; k++)
				c[i+j][k] += a[i][k] * b[j][k];
	for(int i = 0; i <= n; i++) ifwtor(c[i], U);
	for(int i = 0; i < U; i++) printf("%d ", c[cnt1[i]][i].v);
	return 0;
}
