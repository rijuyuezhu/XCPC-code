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
const int MAXN = 4e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m, C[MAXN], D[MAXN], tot, f[MAXN][20], ans[MAXN];
struct Seg {
	int l, r, id;
}a[MAXN];
bool operator < (const Seg& x, const Seg& y) {
	return x.l < y.l;
}
int main() {
	//freopen("flag.in", "r", stdin);
	//freopen("flag.out", "w", stdout);
	n = read(); m = read();
	for(int i = 1; i <= n; i++) C[i] = read(), D[i] = read();
	for(int i = 1; i <= n; i++)  {
		if(C[i] <= D[i]) {
			a[++tot] = (Seg){C[i], D[i], i};
			a[++tot] = (Seg){C[i]+m, D[i]+m, i};
		} else {
			a[++tot] = (Seg){C[i], D[i]+m, i};
			a[++tot] = (Seg){C[i]+m, D[i]+m+m, i};
		}
	}
	sort(a + 1, a + 1 + tot);
	for(int i = 1; i <= tot; i++) {
		int l = i+1, r = tot; f[i][0] = -1;
		while(l <= r) {
			int m = (l + r) >> 1;
			if(a[m].l <= a[i].r) {f[i][0] = m; l = m+1;}
			else r = m-1;
		}
	}
	for(int k = 1; k <= 19; k++)
		for(int i = 1; i <= tot; i++)
			if(f[i][k-1] != -1) 
				f[i][k] = f[f[i][k-1]][k-1];
			else f[i][k] = -1;
	for(int i = 1; i <= n; i++) ans[i] = INF;
	for(int i = 1; i <= tot; i++) {
		int u = i, ret = 0;
		for(int k = 19; k >= 0; k--)
			if(f[u][k] != -1 && a[f[u][k]].r - a[i].l < m)
				ret += 1 << k, u = f[u][k];
		ret++; u = f[u][0];
		if(u != -1 && a[u].r - a[i].l >= m) ans[a[i].id] = min(ans[a[i].id], ret+1);
	}
	for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}
