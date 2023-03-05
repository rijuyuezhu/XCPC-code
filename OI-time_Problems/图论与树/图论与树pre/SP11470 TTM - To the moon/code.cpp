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
char readc() {
	char ch = getchar();
	for(; ch < 'A' || ch > 'Z'; ch = getchar());
	return ch;
}
const int MAXN = 1e5 + 5;
const int MAXNODE = MAXN << 6;
int n, m, tim;
ll A[MAXN];
//Segment_tree 
int rt[MAXN];
int tot;
struct SgtNode {ll v, a; int ls, rs;}e[MAXNODE];
void build(int& o, int l, int r, ll val[]) {
	o = ++tot;
	if(l == r) {e[o].v = val[l]; return ;}
	int m = (l + r) >> 1;
	build(e[o].ls, l, m, val); build(e[o].rs, m+1, r, val);
	e[o].v = e[e[o].ls].v + e[e[o].rs].v;
}
void addrange(int pre, int& o, int l, int r, int x, int y, int k) {
	o = ++tot; e[o] = e[pre];
	if(x <= l && r <= y) {e[o].a += k; return ;}
	int m = (l + r) >> 1;
	if(x <= m) addrange(e[pre].ls, e[o].ls, l, m, x, y, k);
	if(y > m) addrange(e[pre].rs, e[o].rs, m+1, r, x, y, k);
	e[o].v = e[e[o].ls].v + e[e[o].rs].v + e[e[o].ls].a * (m-l+1) + e[e[o].rs].a * (r-m);
}
ll qryrange(int o, int l, int r, int x, int y) {
	if(x <= l && r <= y) return e[o].v + e[o].a * (r - l + 1);
	int m = (l + r) >> 1; ll ans = e[o].a * (y - x + 1);
	if(y <= m) return ans + qryrange(e[o].ls, l, m, x, y);
	else if(x > m) return ans + qryrange(e[o].rs, m+1, r, x, y);
	else return ans + qryrange(e[o].ls, l, m, x, m) + qryrange(e[o].rs, m+1, r, m+1, y);
}

int main() {
	n = read(); m = read();
	for(int i = 1; i <= n; i++) A[i] = read();
	build(rt[0], 1, n, A);
	for(int i = 1; i <= m; i++) {
		char opt = readc();
		if(opt == 'C') {
			int l = read(), r = read(); ll d = read();
			tim++;
			addrange(rt[tim-1], rt[tim], 1, n, l, r, d);
		} else if(opt == 'Q') {
			int l = read(), r = read();
			printf("%lld\n", qryrange(rt[tim], 1, n, l, r));
		} else if(opt == 'H') {
			int l = read(), r = read(), t = read();
			printf("%lld\n", qryrange(rt[t], 1, n, l, r));
		} else tim = read();
	}
	return 0;
}
