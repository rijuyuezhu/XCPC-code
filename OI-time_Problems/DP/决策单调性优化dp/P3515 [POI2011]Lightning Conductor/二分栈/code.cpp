#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e5 + 5;
int n, a[MAXN], que[MAXN], hd, tl, pos[MAXN];
db p[MAXN], Srt[MAXN];
db Y(int i, int j) {return a[j] + Srt[i-j];}
int getpos(int j1, int j2) {
	int l = j2, r = n, ans = j2-1;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(Y(m, j1) >= Y(m, j2)) ans = m, l = m + 1;
		else r = m - 1;
	}
	return ans;
}
void solve() {
	hd = 1; tl = 0;
	for(int i = 1; i <= n; i++) {
		while(hd < tl && pos[tl-1] >= getpos(que[tl], i)) --tl;
		pos[tl] = getpos(que[tl], i); que[++tl] = i;
		while(hd < tl && pos[hd] < i) ++hd;
		p[i] = max(p[i], Y(i, que[hd]));
	}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read(), Srt[i] = sqrt(i);
	solve();
	reverse(a + 1, a + 1 + n); reverse(p + 1, p + 1 + n);
	solve();
	for(int i = n; i >= 1; i--) printf("%d\n", (int)ceil(p[i]) - a[i]);
	return 0;
}
