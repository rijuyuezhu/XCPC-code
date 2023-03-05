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
const int MAXN = 105;
int P=1;
struct mint {
	int v;
	mint(int v = 0) :v(v) {}
};
int MOD(int v) {return v >= P ? v - P : v;}
mint tran(int v) {return MOD(v % P + P);}
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator += (mint& a, mint b) {return a = a + b;}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator -= (mint& a, mint b) {return a = a - b;}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
mint operator *= (mint a, mint b) {return a = a * b;}
mint qpow(mint a, int n) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
int n, l, lim;
struct Mat {
	mint a[MAXN][MAXN];
	void clear() {
		for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) a[i][j] = 0;
	}
	void setu() {
		for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) a[i][j] = (i == j);
	}
	mint* operator [] (int k) {return a[k];}
	const mint* operator [] (int k) const {return a[k];}
};
Mat operator * (const Mat& a, const Mat& b) {
	Mat c; c.clear();
	for(int i = 0; i <= n; i++)
		for(int k = 0; k <= n; k++)
			for(int j = 0; j <= n; j++)
				c[i][j] += a[i][k] * b[k][j];
	return c;
}
Mat qpow(Mat a, int n) {Mat ret; ret.setu(); for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}


mint f[2][MAXN * MAXN][MAXN];
mint C[MAXN * MAXN][MAXN];
int main() {
	n = read(), l = read(), P = read();
	lim = 0;
	f[0][0][0] = 1;
	for(int i = 1; i <= n; i++) {
		int p = i & 1, pre = p ^ 1;
		for(int j = 0; j <= lim; j++)
			for(int k = 0; k <= n; k++) {
				f[p][j][k] = 0;
				if(k >= 1) f[p][j][k] += k * f[pre][j][k-1];
				if(j >= i) f[p][j][k] += 2 * k * f[pre][j-i][k];
				if(j >= 2 * i) f[p][j][k] += k * f[pre][j-2*i][k+1];
			}
		lim += 2 * i;
	}
	lim = min(lim, l - 1);
	Mat T; T.clear();
	for(int i = 0; i <= n; i++) {
		T[i][i] = 1;
		if(i > 0) T[i][i-1] = 1;
	}
	T = qpow(T, l - 1 + n - lim);
	for(int i = 0; i <= n; i++) C[0][i] = T[i][0];
	for(int i = 1; i <= lim; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= n; j++) C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
	mint ans = 0;
	for(int i = 0; i <= lim; i++)
		ans += C[i][n] * f[n & 1][lim - i][1];
	printf("%d\n", ans.v);
	return 0;
}
