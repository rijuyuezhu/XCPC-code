#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
int n, tot = 1, upto[MAXN], sz[MAXN], dfn[MAXN], tim;
ll ans;
char s[MAXN];
vector<int> G[MAXN];
struct Node {
	int ch[26], fl;
}e[MAXN];
void ins(char s[]) {
	int k = strlen(s);
	int p = 1;
	for(int i = k-1; i >= 0; i--) {
		if(!e[p].ch[s[i] - 'a']) 
			e[p].ch[s[i] - 'a'] = ++tot;
		p = e[p].ch[s[i] - 'a'];
	}
	e[p].fl = 1;
}
int getup(int p) {return p == upto[p] ? p : upto[p] = getup(upto[p]);}
void rebuild(int u) {
	for(int i = 0; i < 26; i++) if(e[u].ch[i]) {
		int v = e[u].ch[i];
		if(e[v].fl) {
			G[getup(u)].push_back(v);
		} else {
			upto[getup(v)] = getup(u);
		}
		rebuild(v);
	}
}
bool cmp(int a, int b) {return sz[a] < sz[b];}
void dfs1(int u) {
	sz[u] = 1;
	for(int i = 0; i < (int)G[u].size(); i++) {
		dfs1(G[u][i]);
		sz[u] += sz[G[u][i]];
	}
	sort(G[u].begin(), G[u].end(), cmp);
}

void dfs2(int u, int lst) {
	dfn[u] = ++tim; 
	ans += dfn[u] - lst;
	for(int i = 0; i < (int)G[u].size(); i++) dfs2(G[u][i], dfn[u]);
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		scanf("%s", s);
		ins(s);
	}
	for(int i = 1; i <= tot; i++) upto[i] = i;
	rebuild(1);
	dfs1(1);
	for(int i = 0; i < (int)G[1].size(); i++)
		dfs2(G[1][i], 0);
	printf("%lld\n", ans);
	return 0;
}
