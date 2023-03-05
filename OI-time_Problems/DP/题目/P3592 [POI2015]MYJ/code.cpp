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
const int MAXN = 55, MAXM = 4005;
ll n, m, a[MAXM], b[MAXM], c[MAXM], lsh[MAXM], tot, g[MAXN][MAXM], f[MAXN][MAXN][MAXM], pos[MAXN][MAXN][MAXM], lstk[MAXN][MAXN][MAXM], ans[MAXN];

void LSH() {
	sort(lsh + 1, lsh + 1 + tot);
	tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(ll x) {
	return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}


void getans(int l, int r, int k) {
	if(k > tot) return;
	if(l > r) return;
	k = lstk[l][r][k];
	ans[pos[l][r][k]] = lsh[k];
	getans(l, pos[l][r][k] - 1, k);
	getans(pos[l][r][k] + 1, r, k);
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= m; i++) a[i] = read(), b[i] = read(), c[i] = read(), lsh[++tot] = c[i];
	LSH();
	for(int i = 1; i <= m; i++) c[i] = LSH(c[i]);

	for(int len = 1; len <= n; len++)
		for(int l = 1; l + len - 1 <= n; l++) {
			int r = l + len - 1;
			
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= tot; j++)
					g[i][j] = 0;
			for(int i = 1; i <= m; i++)
				if(l <= a[i] && b[i] <= r)
					g[a[i]][c[i]]++, g[b[i]+1][c[i]]--;
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= tot; j++)
					g[i][j] += g[i-1][j];
			for(int i = 1; i <= n; i++)
				for(int j = tot; j >= 1; j--)
					g[i][j] += g[i][j+1];

			for(int k = tot; k >= 1; k--) {
				for(int p = l; p <= r; p++) {
					ll val = (p > l ? f[l][p-1][k] : 0) + (p < r ? f[p+1][r][k] : 0) + lsh[k] * g[p][k];
					if(f[l][r][k] <= val) {
						f[l][r][k] = val;
						pos[l][r][k] = p;
					}
				}
				if(f[l][r][k] >= f[l][r][k+1]) lstk[l][r][k] = k;
				else f[l][r][k] = f[l][r][k+1], lstk[l][r][k] = lstk[l][r][k+1];
			}
		}
	printf("%lld\n", f[1][n][1]);
	getans(1, n, 1);
	for(int i = 1; i <= n; i++) printf("%lld ", ans[i] ? ans[i] : 1);
	printf("\n");
	return 0;
}
