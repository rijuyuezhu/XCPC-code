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
const int MAXN = 105, MAXV = 2e6 + 5;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, m, a[MAXN], b[MAXN], fac[MAXV], ifac[MAXV], d[MAXN][MAXN];
void init() {
	fac[0] = 1; for(int i = 1; i < MAXV; i++) fac[i] = mul(fac[i-1], i);
	ifac[MAXV-1] = qpow(fac[MAXV-1], P-2); for(int i = MAXV-2; i >= 0; i--) ifac[i] = mul(ifac[i+1], i+1);
}
int det(int a[][MAXN], int n) {
	int ans = 1, f = 0;
	for(int i = 1; i <= n; i++) {
		int mx = i;
		for(int j = i+1; j <= n; j++)
			if(a[j][i] > a[mx][i]) mx = j;
		if(!a[mx][i]) return 0;
		if(mx != i) {
			for(int k = i; k <= n; k++) swap(a[i][k], a[mx][k]);
			f ^= 1;
		}
		int tmp = qpow(a[i][i], P-2);
		for(int j = i+1; j <= n; j++) {
			int t = mul(a[j][i], tmp);
			for(int k = i; k <= n; k++)
				a[j][k] = mns(a[j][k], mul(t, a[i][k]));
		}
		ans = mul(ans, a[i][i]);
	}
	return f ? mns(0, ans) : ans;
}
int C(int n, int m) {
	if(n < 0 || m < 0 || n < m) return 0;
	return mul(fac[n], mul(ifac[m], ifac[n-m]));
}
void work() {
	n = read(), m = read();
	for(int i = 1; i <= m; i++) a[i] = read(), b[i] = read();
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= m; j++)
			d[i][j] = C(b[j] - a[i] + n - 1, n - 1);
	printf("%d\n", det(d, m));
}
int main() {
	init();
	int T = read();
	while(T--) work();
	return 0;
}
