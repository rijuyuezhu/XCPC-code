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
const int MAXN = 1e6 + 5;
int n, t, k, ians;
bool vis[MAXN];
char s[MAXN], ans[MAXN];

//SAM
struct Node{int len, fa, ch[26];}e[MAXN];
ll sum[MAXN], val[MAXN];
int tot = 1, sz[MAXN], c[MAXN], seq[MAXN];
int ins(int c, int lst) {
	int p = lst, np = ++tot; e[np].len = e[p].len + 1;
	for(; p && !e[p].ch[c]; p = e[p].fa) e[p].ch[c] = np;
	if(!p) e[np].fa = 1;
	else {
		int q = e[p].ch[c];
		if(e[q].len == e[p].len + 1) e[np].fa = q;
		else {
			int nq = ++tot; e[nq] = e[q];
			e[nq].len = e[p].len + 1;
			e[np].fa = e[q].fa = nq;
			for(; p && e[p].ch[c] == q; p = e[p].fa) e[p].ch[c] = nq;
		}
	}
	return np;
}
void dfs(int u) {
	if(vis[u]) return ;
	vis[u] = 1;
	sum[u] = val[u] = (u == 1 ? 0 : (t == 0 ? 1 : sz[u]));
	for(int i = 0; i < 26; i++) if(e[u].ch[i]) {
		dfs(e[u].ch[i]);
		sum[u] += sum[e[u].ch[i]];
	}
}
void qry(int u, int k) {
	if(sum[u] < k) return;
	if(k <= val[u]) return; 
	k -= val[u];
	for(int i = 0; i < 26; i++) if(e[u].ch[i]) {
		int v = e[u].ch[i];
		if(k <= sum[v]) {
			ans[++ians] = i + 'a';
			qry(v, k);
			return;
		} else k -= sum[v];
	}
}
int main() {
	scanf("%s", s); n = strlen(s);
	t = read(), k = read();
	int lst = 1;
	for(int i = 0; i < n; i++) {
		lst = ins(s[i] - 'a', lst);
		sz[lst]++;
	}
	for(int i = 2; i <= tot; i++) c[e[i].len]++;
	for(int i = 1; i <= n; i++) c[i] += c[i-1];
	for(int i = tot; i >= 2; i--) seq[c[e[i].len]--] = i;
	for(int i = tot-1; i >= 1; i--) {
		int t = seq[i];
		sz[e[t].fa] += sz[t];
	}
	dfs(1);	
	qry(1, k);
	ans[ians+1] = '\0';
	if(!ians) printf("-1\n");
	else printf("%s\n", ans+1);
	return 0;
}
