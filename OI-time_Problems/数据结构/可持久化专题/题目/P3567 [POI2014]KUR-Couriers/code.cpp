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
const int MAXN = 5e5 + 5;
const int MAXNODE = MAXN << 5;
int n, m, a[MAXN], tot, rt[MAXN];

struct SgtNode{int ls, rs, val;}e[MAXNODE];
void pushup(int o) {e[o].val = e[e[o].ls].val + e[e[o].rs].val;}
void update(int& o, int pre, int l, int r, int x) {
	o = ++tot; e[o] = e[pre];
	if(l == r) {e[o].val++; return ;}
	int m = (l + r) >> 1;
	if(x <= m) update(e[o].ls, e[pre].ls, l, m, x);
	else update(e[o].rs, e[pre].rs, m+1, r, x);
	pushup(o);
}
int qry(int a, int b, int l, int r, int k) {
	if(2 * (e[b].val - e[a].val) <= k) return 0;
	if(l == r) return l;
	int m = (l + r) >> 1;
	if(2 * (e[e[b].ls].val - e[e[a].ls].val) > k) return qry(e[a].ls, e[b].ls, l, m, k);
	else if(2 * (e[e[b].rs].val - e[e[a].rs].val) > k) return qry(e[a].rs, e[b].rs, m+1, r, k);
	else return 0;
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) update(rt[i], rt[i-1], 0, n, a[i]);
	for(int i = 1; i <= m; i++) {
		int l = read(), r = read();
		printf("%d\n", qry(rt[l-1], rt[r], 0, n, r-l+1));
	}
	return 0;
}
