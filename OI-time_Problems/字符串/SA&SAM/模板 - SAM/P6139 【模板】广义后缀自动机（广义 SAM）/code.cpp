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
const int MAXN = 2e6 + 5;
int n;
char s[MAXN];
struct Node{int ch[26], fa, len;}e[MAXN];
int tot = 1;
int ins(int c, int lst) {
	if(e[lst].ch[c]) {
		int p = lst, q = e[lst].ch[c];
		if(e[q].len == e[p].len + 1) return q;
		else {
			int nq = ++tot; e[nq] = e[q];
			e[nq].len = e[p].len + 1;
			for(; p && e[p].ch[c] == q; p = e[p].fa) e[p].ch[c] = nq;
			e[q].fa = nq;
			return nq;
		}
	}
	int p = lst, np = ++tot; e[np].len = e[p].len + 1;
	for(; p && !e[p].ch[c]; p = e[p].fa) e[p].ch[c] = np;
	if(!p) e[np].fa = 1;
	else {
		int q = e[p].ch[c];
		if(e[q].len == e[p].len + 1) e[np].fa = q;
		else {
			int nq = ++tot; e[nq] = e[q];
			e[nq].len = e[p].len + 1;
			for(; p && e[p].ch[c] == q; p = e[p].fa) e[p].ch[c] = nq;
			e[np].fa = e[q].fa = nq;
		}
	}
	return np;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		scanf("%s", s+1);
		int len = strlen(s+1), lst = 1;
		for(int j = 1; j <= len; j++) lst = ins(s[j] - 'a', lst);
	}
	ll ans = 0;
	for(int i = 2; i <= tot; i++) ans += e[i].len - e[e[i].fa].len;
	printf("%lld\n", ans);
	return 0;
}
