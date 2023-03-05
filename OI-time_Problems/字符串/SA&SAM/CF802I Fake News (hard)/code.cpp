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
const int MAXN = 2e5 + 5;
int n, sz[MAXN], c[MAXN], seq[MAXN];
ll ans;
char s[MAXN];
struct Node {int fa, len, ch[26];}e[MAXN];
int tot = 1;
int getnd() {
	++tot; e[tot] = (Node){0, 0, {0}};
	return tot;
}
int ins(int c, int lst) {
	int p = lst, np = getnd(); e[np].len = e[p].len + 1;
	for(; p && !e[p].ch[c]; p = e[p].fa) e[p].ch[c] = np;
	if(!p) e[np].fa = 1;
	else {
		int q = e[p].ch[c];
		if(e[q].len == e[p].len + 1) e[np].fa = q;
		else {
			int nq = getnd(); e[nq] = e[q];
			e[nq].len = e[p].len + 1;
			e[np].fa = e[q].fa = nq;
			for(; p && e[p].ch[c] == q; p = e[p].fa) e[p].ch[c] = nq;
		}
	}
	return np;
}


void work() {
	tot = 1; e[1] = (Node){0, 0, {0}};
	int lst = 1;
	scanf("%s", s+1); n = strlen(s+1);
	memset(sz, 0x00, sizeof sz);
	for(int i = 1; i <= n; i++) {
		lst = ins(s[i] - 'a', lst);
		sz[lst]++;
	}
	for(int i = 0; i <= n; i++) c[i] = 0;
	for(int i = 2; i <= tot; i++) c[e[i].len]++;
	for(int i = 1; i <= n; i++) c[i] += c[i-1];
	for(int i = tot; i >= 2; i--) seq[c[e[i].len]--] = i;
	for(int i = tot-1; i >= 1; i--) sz[e[seq[i]].fa] += sz[seq[i]];
	ans = 0;
	for(int i = 2; i <= tot; i++) ans += 1ll * sz[i] * sz[i] * (e[i].len - e[e[i].fa].len);
	printf("%lld\n", ans);
}
int main() {
	int T = read();
	while(T--) work();
	return 0;
}
