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
const int MAXN = 105, MAXW = 4e4 + 5;
int n, m, v[MAXN], w[MAXN], c[MAXN], Q[MAXW], K[MAXW], hd, tl, f[MAXW];
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) v[i] = read(), w[i] = read(), c[i] = read();
	for(int i = 1; i <= n; i++) {
		for(int r = 0; r < w[i]; r++) {
			int lim = (m - r) / w[i];
			hd = 1; tl = 0;
			for(int t = 0; t <= lim; t++) {
				int tmp = f[t * w[i] + r] - t * v[i];
				while(hd <= tl && Q[tl] <= tmp) --tl;
				Q[++tl] = tmp, K[tl] = t;
				while(hd <= tl && K[hd] < t - c[i]) ++hd;
				if(hd <= tl) f[t * w[i] + r] = max(f[t * w[i] + r], Q[hd] + t * v[i]);
			}
		}
	}
	printf("%d\n", f[m]);
	return 0;
}
