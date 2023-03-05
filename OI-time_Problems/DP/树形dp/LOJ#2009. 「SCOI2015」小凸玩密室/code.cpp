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
const int MAXN = 2e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
#define check(u) ((u) >= 1 && (u) <= n)
#define fa(u, k) ((u) / (1 << (k)))
#define bro(u) (check(u) ? (u) ^ 1 : 0)
#define br(u, k) bro(fa(u, k-1))
#define ls(u) ((u) << 1)
#define rs(u) ((u) << 1 | 1)
int n;
ll A[MAXN], b[MAXN], dist[MAXN], f[MAXN][21], g[MAXN][21], ans;

int main() {
	n = read();
	for(int i = 1; i <= n; i++) A[i] = read();
	for(int i = 2; i <= n; i++) b[i] = read();
	A[0] = 0; b[1] = 0;
	for(int i = 1; i <= n; i++) dist[i] = dist[fa(i, 1)] + b[i];
	for(int i = n; i >= 1; i--) {
		if(!check(ls(i)) && !check(rs(i))) {
			for(int j = 1; j <= 19; j++) {
				f[i][j] = A[fa(i, j)] * (dist[i] - dist[fa(i, j)]);
				g[i][j] = A[br(i, j)] * (dist[i] + dist[br(i, j)] - 2 * dist[fa(i, j)]);
			}
		} else if(!check(rs(i))) {
			for(int j = 1; j <= 19; j++) {
				f[i][j] = A[ls(i)] * b[ls(i)] + f[ls(i)][j+1];
				g[i][j] = A[ls(i)] * b[ls(i)] + g[ls(i)][j+1];
			}
		} else {
			for(int j = 1; j <= 19; j++) {
				f[i][j] = min(
								g[ls(i)][1] + A[ls(i)] * b[ls(i)] + f[rs(i)][j+1],
								g[rs(i)][1] + A[rs(i)] * b[rs(i)] + f[ls(i)][j+1]
							 );
				g[i][j] = min(
								g[ls(i)][1] + A[ls(i)] * b[ls(i)] + g[rs(i)][j+1],
								g[rs(i)][1] + A[rs(i)] * b[rs(i)] + g[ls(i)][j+1]
							 );
			}
		}
	}
	ans = INF;
	for(int u = 1; u <= n; u++) {
		ll ret = f[u][1];
		for(int i = u; i; i = fa(i, 1)) {
			if(check(bro(i))) {
				ret += A[bro(i)] * b[bro(i)] + f[bro(i)][2];
			} else {
				ret += A[fa(i, 2)] * b[fa(i, 1)];
			}
		}
		ans = min(ans, ret);
	}
	printf("%lld\n", ans);
	return 0;
}
