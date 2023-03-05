#include<algorithm>
#include<cstdio>
#include<vector>
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
const int MAXN = (1 << 17) + 5, Bas = 1 << 17, P = 998244353;
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
	mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
	mint operator += (mint& a, mint b) {return a = a + b;}
	mint operator -= (mint& a, mint b) {return a = a - b;}
	mint operator *= (mint& a, mint b) {return a = a * b;}
	const mint inv2 = 499122177;
} using namespace MINT;
namespace Poly {
	typedef vector<mint> poly;
	void OR(poly& f, int lim, int ty) {
		for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
			for(int i = 0; i < lim; i += l)
				for(int j = i; j < i + k; j++) {
					if(ty) f[j+k] += f[j];
					else f[j+k] -= f[j];
				}
	}
	void AND(poly& f, int lim, int ty) {
		for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
			for(int i = 0; i < lim; i += l)
				for(int j = i; j < i + k; j++) {
					if(ty) f[j] += f[j+k];
					else f[j] -= f[j+k];
				}
	}
	void XOR(poly& f, int lim, int ty) {
		for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1)
			for(int i = 0; i < lim; i += l)
				for(int j = i; j < i + k; j++) {
					mint t = f[j+k];
					f[j+k] = f[j] - t;
					f[j] = f[j] + t;
					if(!ty) f[j] *= inv2, f[j+k] *= inv2;
				}
	}
	poly MulOR(poly f, poly g) {
		int n = f.size();
		OR(f, n, 1); OR(g, n, 1);
		for(int i = 0; i < n; i++) f[i] = f[i] * g[i];
		OR(f, n, 0);
		return f;
	}
	poly MulAND(poly f, poly g) {
		int n = f.size();
		AND(f, n, 1); AND(g, n, 1);
		for(int i = 0; i < n; i++) f[i] = f[i] * g[i];
		AND(f, n, 0);
		return f;
	}
	poly MulXOR(poly f, poly g) {
		int n = f.size();
		XOR(f, n, 1); XOR(g, n, 1);
		for(int i = 0; i < n; i++) f[i] = f[i] * g[i];
		XOR(f, n, 0);
		return f;
	}
} using namespace Poly;

int n;
poly f, g, h;
int main() {
	n = read(); n = 1 << n;
	f.resize(n); g.resize(n);
	for(int i = 0; i < n; i++) f[i] = read();
	for(int i = 0; i < n; i++) g[i] = read();
	h = MulOR(f, g);
	for(int i = 0; i < n; i++) printf("%d ", h[i].v);
	printf("\n");
	h = MulAND(f, g);
	for(int i = 0; i < n; i++) printf("%d ", h[i].v);
	printf("\n");
	h = MulXOR(f, g);
	for(int i = 0; i < n; i++) printf("%d ", h[i].v);
	printf("\n");
	return 0;
}
