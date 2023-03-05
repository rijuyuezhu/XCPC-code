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
typedef pair<int, int> pii;
const int MAXN = 5005;
const int MAXM = 2e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m, fl, ans, upto[MAXN];
struct Edge {int u, v, w;}e[MAXM];
pii E[MAXN];
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
void solve() {
	for(int i = 1; i <= n; i++) upto[i] = i;
	int tot = 0;
	while(tot < n - 1) {
		int upd = 0;
		for(int i = 1; i <= n; i++) E[i] = pii(INF, INF);
		for(int i = 1; i <= m; i++) {
			int fu = getup(e[i].u), fv = getup(e[i].v);
			if(fu == fv) continue;
			upd = 1;
			E[fu] = min(E[fu], pii(e[i].w, i));
			E[fv] = min(E[fv], pii(e[i].w, i));
		}
		if(!upd) break;
		for(int i = 1; i <= m; i++) {
			int fu = getup(e[i].u), fv = getup(e[i].v);
			if(fu == fv) continue;
			if(E[fu].second == i || E[fv].second == i) {
				upto[fu] = fv; ans += e[i].w; tot++;
			}
		}
	}
	if(tot < n - 1) fl = 1;			
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= m; i++) {
		e[i].u = read(); e[i].v = read(); e[i].w = read();
	}
	solve();
	if(fl) printf("orz\n");
	else printf("%d\n", ans);
	return 0;
}
