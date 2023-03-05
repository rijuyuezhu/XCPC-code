#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int P = 1e9 + 7, MAXL = 2e6 + 5;
namespace MINT {
	struct mint {
		int v;
		mint(int v = 0) : v(v) {}
	};
	int MOD(int v) {return v >= P ? v - P : v;}
	int tran(int v) {return MOD(v % P + P);}
	mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
	mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
	mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
	mint qpow(mint a, int n = P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
} using namespace MINT;
namespace SAM {
	struct Node {int ch[26], len, fa;} e[MAXL]; 
	int tot;
	int insert(int c, int lst, int rt) {//rt is the node refering to emptystring in current string
		int p = lst, np = ++tot; e[np].len = e[p].len + 1;
		for(; p && !e[p].ch[c]; p = e[p].fa) e[p].ch[c] = np;
		if(!p) e[np].fa = rt;
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
		return np;
	}
} using namespace SAM;
int Rt[MAXL], n, vis[MAXL];
char s[MAXL];
mint f[MAXL];
void dfs(int u) {
	if(vis[u]) return ;
	vis[u] = 1; f[u] = 1;
	for(int c = 0; c < 26; c++)
		if(e[u].ch[c]) {
			int v = e[u].ch[c];
			dfs(v); f[u] = f[u] + f[v];
		}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		scanf("%s", s+1); int len = strlen(s+1);
		Rt[i] = ++tot; int lst = tot;
		for(int j = 1; j <= len; j++) lst = insert(s[j] - 'a', lst, Rt[i]);
	}
	for(int i = n-1; i >= 1; i--)
		for(int j = Rt[i]; j < Rt[i+1]; j++) {
			for(int c = 0; c < 26; c++) if(!e[j].ch[c]) e[j].ch[c] = e[Rt[i+1]].ch[c];
		}
	dfs(Rt[1]);
	printf("%d\n", f[Rt[1]].v);
	return 0;
}
