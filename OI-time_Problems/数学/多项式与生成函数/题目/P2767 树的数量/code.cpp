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
const int P = 10007;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
	int v;
	mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint qpow(mint a, int n) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
int n, m;
mint fac[P], ifac[P], inv[P];
mint C(int n, int m) {
	if(n < m || n < 0 || m < 0) return 0;
	return fac[n] * ifac[m] * ifac[n-m];
}
mint Lucas(int n, int m) {
	if(n < m) return 0;
	if(!m) return 1;
	return C(n % P, m % P) * Lucas(n / P, m / P);
}
int main() {
	n = read(), m = read();
	inv[1] = 1; for(int i = 2; i < P; i++) inv[i] = (P - P / i) * inv[P % i];
	fac[0] = ifac[0] = 1;
	for(int i = 1; i < P; i++) {
		fac[i] = fac[i-1] * i;
		ifac[i] = ifac[i-1] * inv[i];
	}
	printf("%d\n", (Lucas(n * m, n - 1) * inv[n]).v);
	return 0;
}
