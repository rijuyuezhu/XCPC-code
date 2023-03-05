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
const int MAXN = 1e5 + 5;
int n;
char s[MAXN];
ll f[MAXN];
struct SAM_Node{int ch[26], fa, len;}e[MAXN];
int lst, tot;
void ins(int c) {
	int p = lst, np = lst = ++tot;
	e[np].len = e[p].len + 1;
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
void clear() {
	memset(e, 0x00, sizeof e);
	tot = lst = 1;
}
void dp(int u) {
	if(~f[u]) return;
	f[u] = 1;
	for(int i = 0; i < 26; i++) if(e[u].ch[i]) {
		dp(e[u].ch[i]); f[u] += f[e[u].ch[i]];
	}
}
void solve() {
	scanf("%s", s+1); n = strlen(s+1);
	for(int i = 1; i <= n; i++) ins(s[i] - 'a');
	memset(f, -1, sizeof f);
	dp(1);
	printf("%lld\n", f[1] - 1);
}
int main() {
	int T = read();
	while(T--) {
		clear();
		solve();
	}
	return 0;
}
