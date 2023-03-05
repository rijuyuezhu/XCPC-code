#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5;
const int MAXK = 205;
const db INF = 1e50;
int n, K, q[MAXN], hd, tl, pre[MAXN][MAXK];
ll a[MAXN], S[MAXN], dp[MAXN][MAXK];
ll sqr(ll x) {return x * x;}
ll Y(int i, int k) {
	return sqr(S[i]) - dp[i][k-1];
}
db slope(int i, int j, int k) {
	if(S[i] == S[j]) return Y(i, k) >= Y(j, k) ? INF : -INF;
	return db(Y(i, k) - Y(j, k)) / (S[i] - S[j]);
}
void dfs(int n, int k) {
	if(k == 0) return;
	dfs(pre[n][k], k-1);
	printf("%d ", pre[n][k]);
}
int main() {
	n = read(); K = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) S[i] = S[i-1] + a[i];
	for(int k = 1; k <= K; k++) {
		int hd = 1, tl = 0;
		q[++tl] = 0;
		for(int i = 1; i <= n; i++) {
			while(hd < tl && slope(q[hd], q[hd+1], k) <= S[i]) hd++;
			pre[i][k] = q[hd];
			dp[i][k] = dp[q[hd]][k-1] + (S[i] - S[q[hd]]) * S[q[hd]];
			while(hd < tl && slope(q[tl-1], q[tl], k) >= slope(q[tl], i, k)) tl--;
			q[++tl] = i;
		}
	}
	printf("%lld\n", dp[n][K]);
	dfs(n, K);
	printf("\n");
	return 0;
}
