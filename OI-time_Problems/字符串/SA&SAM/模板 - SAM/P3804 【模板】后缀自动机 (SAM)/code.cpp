#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 2e6 + 5;//the num of sam is 2*n
namespace SAM {
	struct Node{int ch[26], fa, len;}e[MAXN];
	int lst = 1, tot = 1, sz[MAXN];
	void ins(int c) {
		int p = lst, np = lst = ++tot; e[np].len = e[p].len + 1; sz[np]++;
		for(; p && !e[p].ch[c]; p = e[p].fa) e[p].ch[c] = np;
		if(!p) e[np].fa = 1;
		else {
			int q = e[p].ch[c];
			if(e[q].len == e[p].len + 1) e[np].fa = q;
			else {
				int nq = ++tot; e[nq] = e[q];
				e[nq].len = e[p].len + 1; e[q].fa = e[np].fa = nq;
				for(; p && e[p].ch[c] == q; p = e[p].fa) e[p].ch[c] = nq;
			}
		}
	}
	int head[MAXN], ver[MAXN], nxt[MAXN], cnt;
	void addedge(int u, int v) {
		ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
	}
	void build() {
		for(int i = 2; i <= tot; i++) addedge(e[i].fa, i);
	}
	void dfs(int u, ll& ans) {
		for(int i = head[u]; i; i = nxt[i]) {
			dfs(ver[i], ans); sz[u] += sz[ver[i]];
		}
		if(sz[u] > 1) ans = max(ans, 1ll * sz[u] * e[u].len);
	}
}
using namespace SAM;
char s[MAXN];
int n;
ll ans;
int main() {
	scanf("%s", s+1); n = strlen(s+1);
	for(int i = 1; i <= n; i++) ins(s[i] - 'a');
	build();
	dfs(1, ans);
	printf("%lld\n", ans);
	return 0;
}
