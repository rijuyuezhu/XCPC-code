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
char s[MAXN];
int n;

struct Node{int ch[26], fa, len;}e[MAXN];
int lst, tot;
void ins(int c) {
	int p = lst, np = lst = ++tot; e[np].len = e[p].len + 1;
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
	lst = tot = 1; memset(e, 0x00, sizeof e);
}

void solve() {
	scanf("%s", s+1); n = strlen(s+1);
	for(int i = 1; i <= n; i++) ins(s[i] - 'a');
	ll ans = 0;
	for(int i = 2; i <= tot; i++) ans += e[i].len - e[e[i].fa].len;
	printf("%lld\n", ans);
}
int main() {
	int T = read();
	while(T--) {
		clear();
		solve();
	}
	return 0;
}
