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
const int MAXN = 5e6 + 5;
const db Pi = acos(-1.0);
struct cp{db x, y;}f[MAXN];
cp operator + (const cp& a, const cp& b) {return (cp){a.x+b.x, a.y+b.y};}
cp operator - (const cp& a, const cp& b) {return (cp){a.x-b.x, a.y-b.y};}
cp operator * (const cp& a, const cp& b) {return (cp){a.x*b.x - a.y*b.y, a.x*b.y + a.y * b.x};}
int n, m, d, id[MAXN];
void fft(cp* f, int fl) {
	for(int i = 0; i < d; i++) if(i < id[i]) swap(f[i], f[id[i]]);
	for(int l = 2, hl = 1; l <= d; l <<= 1, hl <<= 1) {
		cp w0 = (cp){cos(2*Pi / l), fl * sin(2*Pi / l)};
		for(int i = 0; i < d; i += l) {
			cp w = (cp){1, 0};
			for(int j = i; j < i + hl; j++, w = w * w0) {
				cp tt = w * f[j+hl];
				f[j+hl] = f[j] - tt;
				f[j] = f[j] + tt;
			}
		}
	}
	if(fl == -1) {
		for(int i = 0; i < d; i++) f[i].x /= d, f[i].y /= d;
	}
}
int main() {
	n = read(), m = read();
	for(int i = 0; i <= n; i++) f[i].x = read();
	for(int i = 0; i <= m; i++) f[i].y = read();
	for(d = 1; d <= n+m; d <<= 1);
	for(int i = 0; i < d; i++) id[i] = (id[i >> 1] >> 1) | ((i & 1) ? (d >> 1) : 0);
	fft(f, 1);
	for(int i = 0; i < d; i++) f[i] = f[i] * f[i];
	fft(f, -1);
	for(int i = 0; i < d; i++) f[i].y /= 2;
	for(int i = 0; i <= n+m; i++) printf("%d ", int(f[i].y + 0.5));
	return 0;
}
