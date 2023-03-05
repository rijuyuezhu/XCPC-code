#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1 << 20;
const db PI = acos(-1.0);
struct cp{db x, y;};
cp operator + (const cp& a, const cp& b) {return (cp){a.x+b.x, a.y+b.y};}
cp operator - (const cp& a, const cp& b) {return (cp){a.x-b.x, a.y-b.y};}
cp operator * (const cp& a, const cp& b) {return (cp){a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x};}
int tr[MAXN], tf;
void tpre(int lim) {
	if(tf == lim) return;
	tf = lim; for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
}
void FFT(cp* f, int lim, int fl) {
	tpre(lim); for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
	for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1) {
		cp w0 = (cp){cos(2 * PI / l), (fl ? 1 : -1) * sin(2 * PI / l)};
		for(int i = 0; i < lim; i += l) {
			cp wn = (cp){1, 0};
			for(int j = i; j < i+k; j++, wn = wn * w0) {
				cp tt = f[j+k] * wn;
				f[j+k] = f[j] - tt;
				f[j] = f[j] + tt;
			}
		}
	}
	if(!fl) {
		for(int i = 0; i < lim; i++) f[i].x /= lim, f[i].y /= lim;
	}
}
//void debug() {
//	int n, m;
//	static cp a[MAXN], b[MAXN];
//	n = read(), m = read();
//	for(int i = 0; i <= n; i++) a[i].x = read();
//	for(int i = 0; i <= m; i++) b[i].x = read();
//	int lim = 1; for(; lim <= n + m; lim <<= 1);
//	FFT(a, lim, 1); FFT(b, lim, 1);
//	for(int i = 0; i < lim; i++) a[i] = a[i] * b[i];
//	FFT(a, lim, 0);
//	for(int i = 0; i <= n+m; i++) printf("%.2lf ", a[i].x);
//}
int n, x, a[MAXN], s[MAXN];
cp f[MAXN], g[MAXN];
ll calc0() {
	int cnt = 0; ll ans = 0; a[n+1] = 1;
	for(int i = 1; i <= n+1; i++) {
		if(a[i] == 0) {
			cnt++;
		} else {
			ans += 1ll * cnt * (cnt + 1) / 2;
			cnt = 0;
		}
	}
	return ans;
}
int main() {
	//debug();	
	n = read(), x = read();
	for(int i = 1; i <= n; i++) a[i] = (read() < x ? 1 : 0);
	for(int i = 1; i <= n; i++) s[i] = s[i-1] + a[i];
	for(int i = 0; i <= n; i++) f[s[i]].x++;
	for(int i = 0; i <= n; i++) g[i] = f[n - i];
	int lim = 1; for(; lim <= n+n; lim <<= 1);
	FFT(f, lim, 1); FFT(g, lim, 1);
	for(int i = 0; i < lim; i++) f[i] = f[i] * g[i];
	FFT(f, lim, 0);
	printf("%lld ", calc0());
	for(int i = 1; i <= n; i++)
		printf("%lld ", ll(f[i + n].x + .5));
	return 0;
}
