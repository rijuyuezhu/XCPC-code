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
const int MAXN = 5e4 + 5, MAXM = 1e5 + 5, inf = 0x3f3f3f3f;
typedef pair<int, int> pr;
#define fi first
#define se second
int n, m, need;
struct Edge {
	int u, v, w, c;
}e[MAXM];
bool operator < (const Edge& a, const Edge& b) { return a.w == b.w ? a.c < b.c : a.w < b.w; }
int upto[MAXN];
void init() { for(int i = 1; i <= n; i++) upto[i] = i; }
int getup(int x) { return x == upto[x] ? x : upto[x] = getup(upto[x]); }
pr check(int k) {
	pr ans = pr(0, 0);
	init();
	for(int i = 1; i <= m; i++)
		if(e[i].c == 0) e[i].w -= k;
	sort(e + 1, e + 1 + m);
	int tot = 0;
	for(int i = 1; i <= m && tot < n-1; i++) {
		int fu = getup(e[i].u), fv = getup(e[i].v);
		if(fu == fv) continue;
		upto[fu] = fv;
		tot++;
		ans.fi += e[i].w;
		if(e[i].c == 0) ans.se++;
	}
	for(int i = 1; i <= m; i++)
		if(e[i].c == 0) e[i].w += k;
	return ans;
}
int main() {
	n = read(); m = read(); need = read();
	for(int i = 1; i <= m; i++) e[i].u = read()+1, e[i].v = read()+1, e[i].w = read(), e[i].c = read();
	int ans = -1;
	int l = -200, r = 200;
	while(l <= r) {
		int mid = (l + r) >> 1;
		pr ret = check(mid);
		if(ret.se >= need) ans = ret.fi + mid * need, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
