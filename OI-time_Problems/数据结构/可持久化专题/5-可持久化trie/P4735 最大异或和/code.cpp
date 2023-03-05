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
char readc() {
	char ch = getchar();
	for(; ch != 'A' && ch != 'Q'; ch = getchar());
	return ch;
}
const int MAXN = 6e5 + 5;
int n, m;
namespace Trie {
	const int MAXNODE = MAXN * 30;
	struct Node{int ch[2], sz;}e[MAXNODE];
	int tot;
	void ins(int& p, int pre, int x, int t) {
		p = ++tot; e[p] = e[pre];
		if(t == -1) {e[p].sz++; return ;}
		int v = (x >> t) & 1;
		e[p].sz++;
		ins(e[p].ch[v], e[pre].ch[v], x, t-1);
	}
	int qry(int a, int b, int x, int t) {
		if(t == -1) return 0;
		int v = (x >> t) & 1;
		if(e[e[b].ch[v^1]].sz - e[e[a].ch[v^1]].sz > 0) return (1 << t) + qry(e[a].ch[v^1], e[b].ch[v^1], x, t-1);
		else if(e[e[b].ch[v]].sz - e[e[a].ch[v]].sz > 0) return qry(e[a].ch[v], e[b].ch[v], x, t-1);
		return 0;
	}
}
int s[MAXN], rt[MAXN];
int main() {
	n = read(), m = read();
	Trie::ins(rt[1], rt[0], 0, 24);
	n++;
	for(int i = 2; i <= n; i++) {
		s[i] = s[i-1] ^ read();
		Trie::ins(rt[i], rt[i-1], s[i], 24);
	}
	for(int i = 1; i <= m; i++) {
		char opt = readc();
		if(opt == 'A') {
			n++; s[n] = s[n-1] ^ read();
			Trie::ins(rt[n], rt[n-1], s[n], 24);
		} else {
			int l = read()+1, r = read()+1, x = read();
			printf("%d\n", Trie::qry(rt[l-2], rt[r-1], s[n] ^ x, 24));
		}
	}
	return 0;
}
