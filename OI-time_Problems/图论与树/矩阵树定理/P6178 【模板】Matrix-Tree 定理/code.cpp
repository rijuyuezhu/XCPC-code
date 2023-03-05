#include<cstring>
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
const int MAXN = 305, P = 1e9 + 7;
namespace MINT {
	struct mint {
		int v;
		mint(int v = 0) :v(v) {}
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
int n, m, ty;
mint a[MAXN][MAXN];
mint det(mint a[][MAXN], int n) {
	int f = 0;
	for(int i = 1; i <= n; i++) {
		int num = -1;
		for(int j = i; j <= n; j++) if(a[j][i].v) {
			num = j; break;
		}
		if(num == -1) return 0;
		if(num != i) {
			f ^= 1;
			for(int j = i; j <= n; j++) swap(a[i][j], a[num][j]);
		}
		mint in = qpow(a[i][i]);
		for(int j = i+1; j <= n; j++) {
			mint t = in * a[j][i];
			for(int k = i; k <= n; k++)
				a[j][k] -= a[i][k] * t;
		}
	}
	mint ans = 1;
	for(int i = 1; i <= n; i++) ans *= a[i][i];
	if(f) ans = 0-ans;
	return ans;
}
int main() {
	n = read(), m = read(), ty = read();
	for(int i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		u--, v--;
		if(!ty) {
			a[u][u] += w; a[v][v] += w;
			a[u][v] -= w; a[v][u] -= w;
		} else {
			a[v][v] += w; a[u][v] -= w;
		}
	}
	printf("%d\n", det(a, n-1).v);
	return 0;
}
