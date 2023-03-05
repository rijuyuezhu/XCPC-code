#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
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
const int MAXN = 3e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, tl, que[MAXN];
ll S, T[MAXN], C[MAXN], P[MAXN], Q[MAXN], f[MAXN];
ll X(int i) {return P[i];}
ll Y(int i) {return f[i] - S * P[i];}
long double slope(int i, int j) {return X(i) == X(j) ? (Y(i) <= Y(j) ? 1e40 : -1e40) : (long double)(Y(i) - Y(j)) / (X(i) - X(j));}
int getpos(ll k) {
	if(tl == 1) return que[tl];
	int l = 1, r = tl-1, ans = tl;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(slope(que[m], que[m+1]) >= k) ans = m, r = m - 1;
		else l = m + 1;
	}
	return que[ans];
}
int main() {
	n = read(); S = read();
	for(int i = 1; i <= n; i++) {
		T[i] = read(); C[i] = read();
		P[i] = P[i-1] + C[i];
		Q[i] = Q[i-1] + T[i];
	}
	tl = 0;
	f[0] = 0; que[++tl] = 0;
	for(int i = 1; i <= n; i++) {
		int j = getpos(Q[i]);
		f[i] = f[j] - S * P[j] - Q[i] * P[j] + P[i] * Q[i] + P[n] * S;
		while(tl > 1 && slope(que[tl-1], que[tl]) >= slope(que[tl], i)) --tl;
		que[++tl] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
