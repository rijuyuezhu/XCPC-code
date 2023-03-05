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
const int MAXN = 5e5 + 5;
char s[MAXN];
struct Node{int ch[26], fa, len;}e[MAXN];
int n, lst = 1, tot = 1, sz[MAXN], head[MAXN], ver[MAXN], nxt[MAXN], cnt, id[MAXN], c[MAXN], col[MAXN], upto[MAXN];
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
int getup(int u) {return u == upto[u] ? u : upto[u] = getup(upto[u]);}
void ins(int c) {
	int p = lst, np = lst = ++tot; sz[np] = 1;
	e[np].len = e[p].len + 1;
	for(; p && !e[p].ch[c]; p = e[p].fa) e[p].ch[c] = np;
	if(!p) e[np].fa = 1;
	else {
		int q = e[p].ch[c];
		if(e[q].len == e[p].len + 1) e[np].fa = q;
		else {
			int nq = ++tot; 
			e[nq] = e[q]; e[nq].len = e[p].len + 1;
			e[q].fa = e[np].fa = nq;
			for(; p && e[p].ch[c] == q; p = e[p].fa) e[p].ch[c] = nq;
		}
	}
}
void dfs(int u) {
	for(int i = head[u]; i; i = nxt[i]) {
		dfs(ver[i]); sz[u] += sz[ver[i]];
	}
}
void cover(int l, int r, int v) {
	for(int i = getup(l); i <= r; i = getup(i+1)) {
		col[i] = v; upto[i] = getup(i+1);
	}
}
int main() {
	scanf("%s", s+1); n = strlen(s+1);
	for(int i = 1; i <= n; i++) ins(s[i] - 'a');
	for(int i = 2; i <= tot; i++) addedge(e[i].fa, i);
	dfs(1);
	for(int i = 1; i <= tot; i++) c[sz[i]]++;
	for(int i = 2; i <= n; i++) c[i] += c[i-1];
	for(int i = tot; i >= 1; i--) id[c[sz[i]]--] = i;
	for(int i = 1; i <= n+1; i++) upto[i] = i;
	for(int i = tot; i >= 1; i--) if(id[i] != 1) {
		int u = id[i];
		int l = max(1, e[e[u].fa].len + 1), r = e[u].len;
		cover(l, r, sz[u]);
	}
	for(int i = 1; i <= n; i++) printf("%d\n", col[i]);
	return 0;
}
