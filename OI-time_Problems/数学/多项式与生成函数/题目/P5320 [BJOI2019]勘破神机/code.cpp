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
const int P = 998244353;
int Mod(int x) {return x >= P ? x - P : x;}
struct modint {
	int x;
	modint(int x = 0) :x(x) {}
};
modint operator + (const modint& a, const modint& b) {return modint(Mod(a.x + b.x));}
modint operator - (const modint& a, const modint& b) {return modint(Mod(a.x - b.x + P));}
modint operator * (const modint& a, const modint& b) {return modint(1ll * a.x * b.x % P);}
modint qpow(modint a, ll n) {modint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
const int MAXK = 510;
modint s[MAXK][MAXK], C[MAXK][MAXK], fac[MAXK], ifac[MAXK];
void init(int K) {
	s[0][0] = C[0][0] = 1;
	for(int i = 1; i <= K; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			C[i][j] = C[i-1][j] + C[i-1][j-1];
			s[i][j] = (i-1) * s[i-1][j] + s[i-1][j-1];
		}
	}
	fac[0] = 1;
	for(int i = 1; i <= K; i++) fac[i] = fac[i-1] * i;
	ifac[K] = qpow(fac[K], P-2);
	for(int i = K-1; i >= 0; i--) ifac[i] = ifac[i+1] * (i+1);
}
namespace Task1 {
	const modint I = 5;
	struct cp {
		modint x, y;
		cp(modint x = 0, modint y = 0) : x(x), y(y) {}
	};
	cp operator + (const cp& a, const cp& b) {return cp(a.x + b.x, a.y + b.y);}
	cp operator - (const cp& a, const cp& b) {return cp(a.x - b.x, a.y - b.y);}
	cp operator * (const cp& a, const cp& b) {return cp(a.x * b.x + I * a.y * b.y, a.x * b.y + a.y * b.x);}
	cp operator * (const cp& a, const modint& b) {return cp(a.x * b, a.y * b);}
	cp qpow_cp(cp a, ll n) {cp ret = cp(1, 0); for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
	const cp
		A = cp(499122177, 299473306),
		B = cp(499122177, 698771047),
		X = cp(499122177, 499122177),
		Y = cp(499122177, 499122176),
		invB = cp(499122179, 499122177),
		invY = cp(499122176, 499122176);
	ll l, r;
	int k;
	cp dbsl(cp q, ll n) {
		if(n == 0) return cp(0, 0);
		if(n & 1) 
			return cp(1, 0) + q * (cp(1, 0) + q) * dbsl(q * q, n / 2);
		else return (cp(1, 0) + q) * dbsl(q * q, n / 2);
	}
	void work() {
		l = read(), r = read(), k = read();
		cp ans = cp(0, 0);
		for(int i = 0; i <= k; i++) {
			cp ret = cp(0, 0), a = cp(1, 0), b = qpow_cp(B, i), x = cp(1, 0), y = qpow_cp(Y, i);
			for(int j = 0; j <= i; j++) {
				cp q = x * y;
				ret = ret + a * b * qpow_cp(q, l) * dbsl(q, r - l + 1) * C[i][j];
				a = a * A; b = b * invB; x = x * X, y = y * invY;
			}
			ret = ret * s[k][i];
			if((k - i) & 1) ans = ans - ret;
			else ans = ans + ret;
		}
		modint t = ans.x * ifac[k] * qpow((r-l+1) % P, P-2);
		printf("%d\n", t.x);
	}
}
namespace Task2 {
	const modint I = 3;
	struct cp {
		modint x, y;
		cp(modint x = 0, modint y = 0) : x(x), y(y) {}
	};
	cp operator + (const cp& a, const cp& b) {return cp(a.x + b.x, a.y + b.y);}
	cp operator - (const cp& a, const cp& b) {return cp(a.x - b.x, a.y - b.y);}
	cp operator * (const cp& a, const cp& b) {return cp(a.x * b.x + I * a.y * b.y, a.x * b.y + a.y * b.x);}
	cp operator * (const cp& a, const modint& b) {return cp(a.x * b, a.y * b);}
	cp qpow_cp(cp a, ll n) {cp ret = cp(1, 0); for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
	const cp
		A = cp(499122177, 166374059),
		B = cp(499122177, 831870294),
		X = cp(2, 1),
		Y = cp(2, 998244352),
		invB = cp(3, 1),
		invY = cp(2, 1);
	ll l, r, l1, r1;
	int k;
	cp dbsl(cp q, ll n) {
		if(n == 0) return cp(0, 0);
		if(n & 1) 
			return cp(1, 0) + q * (cp(1, 0) + q) * dbsl(q * q, n / 2);
		else return (cp(1, 0) + q) * dbsl(q * q, n / 2);
	}
	void work() {
		l1 = read(), r1 = read(), k = read();
		l = (l1 + 1) >> 1, r = r1 >> 1;
		if(l > r) {
			printf("%d\n", 0);
			return ;
		}
		cp ans = cp(0, 0);
		for(int i = 0; i <= k; i++) {
			cp ret = cp(0, 0), a = cp(1, 0), b = qpow_cp(B, i), x = cp(1, 0), y = qpow_cp(Y, i);
			for(int j = 0; j <= i; j++) {
				cp q = x * y;
				ret = ret + a * b * qpow_cp(q, l) * dbsl(q, r - l + 1) * C[i][j];
				a = a * A; b = b * invB; x = x * X, y = y * invY;
			}
			ret = ret * s[k][i];
			if((k - i) & 1) ans = ans - ret;
			else ans = ans + ret;
		}
		modint t = ans.x * ifac[k] * qpow((r1-l1+1) % P, P-2);
		printf("%d\n", t.x);
	}
}
int main() {
	init(505);
	int T = read(), m = read();
	if(m == 2) 
		for(int i = 1; i <= T; i++) Task1::work();
	else 
		for(int i = 1; i <= T; i++) Task2::work();
	return 0;
}
