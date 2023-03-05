#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
typedef long double ld;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5, MAXM = 1e5 + 5, MAXP = 105;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m, p, S[MAXN], P[MAXM], hd, tl, que[MAXM];
ll Q[MAXM], f[MAXM][MAXP];
int X(int i, int k) {return i;}
ll Y(int i, int k) {return f[i][k-1] + Q[i];}
ld slope(int i, int j, int k) {return X(i, k) == X(j, k) ? (Y(i, k) <= Y(j, k) ? 1e40 : -1e40) : ld(Y(i, k)-Y(j, k)) / (X(i, k)-X(j, k));}
int main() {
	n = read(), m = read(), p = read();
	for(int i = 2; i <= n; i++) S[i] = S[i-1] + read();
	for(int i = 1; i <= m; i++) {
		int H = read(), T = read();
		P[i] = T - S[H];
	}
	sort(P + 1, P + 1 + m);
	for(int i = 1; i <= m; i++) Q[i] = Q[i-1] + P[i];
	for(int i = 0; i <= m; i++) for(int k = 0; k <= p; k++) f[i][k] = INF;
	f[0][0] = 0;
	for(int k = 1; k <= p; k++) {
		hd = 1, tl = 0; if(k == 1) que[++tl] = 0;
		for(int i = 1; i <= m; i++) {
			if(f[i][k-1] != INF) {
				while(hd < tl && slope(que[tl-1], que[tl], k) >= slope(que[tl], i, k)) --tl;
				que[++tl] = i;
			}
			while(hd < tl && slope(que[hd], que[hd+1], k) <= P[i]) ++hd;
			if(hd <= tl) {
				int j = que[hd];
				f[i][k] = f[j][k-1] + 1ll * (i-j) * P[i] - (Q[i] - Q[j]);
			} else f[i][k] = INF;
		}
	}
	printf("%lld\n", f[m][p]);
	return 0;
}
