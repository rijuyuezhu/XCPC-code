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
const int MAXN = 3005;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
ll a[MAXN], S[MAXN], f[MAXN][MAXN];
int que[MAXN], hd, tl;
ll getx(int i, int k) {return S[i];}
ll gety(int i, int k) {return f[i][k-1] + S[i] * S[i];}
long double slope(int i, int j, int k) {return getx(i, k) == getx(j, k) ? (gety(i, k) >= gety(j, k) ? 1e40 : -1e40) : ((long double)(gety(j, k) - gety(i, k)) / (getx(j, k) - getx(i, k)));}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++)
		a[i] = read(), S[i] = S[i-1] + a[i];
	f[0][0] = 0; for(int i = 1; i <= n; i++) f[i][0] = -INF;
	for(int k = 1; k <= m; k++) {
		hd = 1; tl = 0;
		for(int i = 0; i <= n; i++) {
			while(hd < tl && slope(que[hd], que[hd+1], k) <= 2 * S[i]) hd++;
			if(hd <= tl) f[i][k] = f[que[hd]][k-1] + (S[i] - S[que[hd]]) * (S[i] - S[que[hd]]);
			else f[i][k] = -INF;
			if(f[i][k-1] == -INF) continue;
			while(hd < tl && slope(que[tl-1], que[tl], k) >= slope(que[tl], i, k)) tl--;
			que[++tl] = i;
		}
	}
	printf("%lld\n", m * f[n][m] - S[n] * S[n]);
	return 0;
}
