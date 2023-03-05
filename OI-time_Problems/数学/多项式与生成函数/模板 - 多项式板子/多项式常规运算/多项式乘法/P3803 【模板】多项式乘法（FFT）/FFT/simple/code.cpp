#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef double db;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const db PI = acos(-1.0);
const int MAXN = 1 << 21;
struct cp{db x, y;};
cp operator + (const cp& a, const cp& b) {return (cp){a.x+b.x, a.y+b.y};}
cp operator - (const cp& a, const cp& b) {return (cp){a.x-b.x, a.y-b.y};}
cp operator * (const cp& a, const cp& b) {return (cp){a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x};}
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
				cp tt = wn * f[j+k];
				f[j+k] = f[j] - tt;
				f[j] = f[j] + tt;
			}
		}
	}
	if(!fl) {
		for(int i = 0; i < lim; i++) f[i].x /= lim, f[i].y /= lim;
	}
}
int n, m;
cp f[MAXN], g[MAXN];
int main() {
	n = read(), m = read();
	for(int i = 0; i <= n; i++) f[i].x = read();
	for(int i = 0; i <= m; i++) g[i].x = read();
	int lim = 1; for(; lim < n + m + 1; lim <<= 1);
	FFT(f, lim, 1); FFT(g, lim, 1);
	for(int i = 0; i < lim; i++) f[i] = f[i] * g[i];
	FFT(f, lim, 0);
	for(int i = 0; i <= n+m; i++) printf("%d ", int(f[i].x + .5));
	return 0;
}
