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
namespace Sgt {
	const int MAXNODE = int(1e5 + 5) << 5;
	struct Node {int ls, rs, sz;}e[MAXNODE];
	int tot;
	void upd(int p) {e[p].sz = e[e[p].ls].sz + e[e[p].rs].sz;}
	void mdypos(int& p, int l, int r, int x) {
		int pre = p; e[p = ++tot] = e[pre];
		e[p].sz++;
		if(l == r) return ;
		int m = (l + r) >> 1;
		if(x <= m) mdypos(e[p].ls, l, m, x);
		else mdypos(e[p].rs, m+1, r, x);
		upd(p);
	}
	int qry(int u, int v, int l, int r, int x, int y) {
		if(x <= l && r <= y) return e[v].sz - e[u].sz;
		int m = (l + r) >> 1;
		if(y <= m) return qry(e[u].ls, e[v].ls, l, m, x, y);
		else if(x > m) return qry(e[u].rs, e[v].rs, m+1, r, x, y);
		else return qry(e[u].ls, e[v].ls, l, m, x, m) + qry(e[u].rs, e[v].rs, m+1, r, m+1, y);
	}
}
using namespace Sgt;
int n, m, a[MAXN], rt[MAXN], lim, b, x, lx, rx;
int isexist(int l, int r) {
	l = max(l, 0), r = min(r, lim);
	if(l > r) return 0;
	return qry(rt[lx-1], rt[rx], 0, lim, l, r) > 0;
}
void work() {
	int ans = 0;
	b = read(), x = read(), lx = read(), rx = read();
	for(int k = 17; k >= 0; k--) {
		if((b >> k) & 1) {
			if(isexist(ans - x, ans + (1 << k) - 1 - x)) ;
			else ans += 1 << k;
		} else {
			if(isexist(ans + (1 << k) - x, ans + (1 << (k+1)) - 1 - x)) ans += 1 << k;
		}
	}
	printf("%d\n", b ^ ans);
}
int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) a[i] = read(), lim = max(lim, a[i]);
	rt[0] = 0;
	for(int i = 1; i <= n; i++) {
		rt[i] = rt[i-1];
		mdypos(rt[i], 0, lim, a[i]);
	}
	while(m--) {
		work();
	}
	return 0;
}
