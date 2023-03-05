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
	for(; ch < 32 || ch > 126; ch = getchar());
	return ch;
}
char readbc() {
	char ch = getchar();
	for(; ch < 'A' || ch > 'Z'; ch = getchar());
	return ch;
}
const int MAXL = 3e6 + 5;
namespace Splay {
#define ls ch[0]
#define rs ch[1]
	int rt, tot;
	struct Node{int ch[2], fa, sz; char v;}e[MAXL];
	int idy(int p) {return e[e[p].fa].rs == p;}
	void upd(int p) {e[p].sz = e[e[p].ls].sz + e[e[p].rs].sz + 1;}
	void rtt(int p) {
		int y = e[p].fa, z = e[y].fa, k = idy(p), s = e[p].ch[k^1];
		e[p].fa = z; e[z].ch[idy(y)] = p;
		e[y].fa = p; e[p].ch[k^1] = y;
		e[s].fa = y; e[y].ch[k] = s;
		upd(y); upd(p);
	}
	void splay(int p, int to) {
		for(int y = e[p].fa; y != to; rtt(p), y = e[p].fa)
			if(e[y].fa != to) rtt(idy(p) == idy(y) ? y : p);
		if(!to) rt = p;
	}
	int kth(int k) {
		k++; int p = rt;
		while(k) {
			if(k <= e[e[p].ls].sz) p = e[p].ls;
			else if(k <= e[e[p].ls].sz + 1) return p;
			else k -= e[e[p].ls].sz + 1, p = e[p].rs;
		}
		return -1;
	}
	void split(int x, int y) {
		int l = kth(x-1), r = kth(y+1);
		splay(l, 0); splay(r, l);
	}
	void build(int& p, int l, int r, char a[], int f) {
		if(l > r) {p = 0; return;}
		int m = (l + r) >> 1;
		e[p = ++tot] = (Node){{0, 0}, f, 1, a[m]};
		build(e[p].ls, l, m-1, a, p);
		build(e[p].rs, m+1, r, a, p);
		upd(p);
	}
	void ins(int x, int n, char a[]) {
		split(x+1, x);
		build(e[e[rt].rs].ls, 1, n, a, e[rt].rs);
		upd(e[rt].rs); upd(rt);
	}
	void del(int x, int n) {
		split(x+1, x+n);
		e[e[rt].rs].ls = 0;
		upd(e[rt].rs); upd(rt);
	}
	void print(int p) {
		if(!p) return;
		print(e[p].ls);
		if(e[p].v) putchar(e[p].v);
		print(e[p].rs);
	}
	void getprint(int x, int n) {
		split(x+1, x+n);
		print(e[e[rt].rs].ls);
	}
}
using namespace Splay;
int pr;

char s[MAXL];
int main() {
	rt = 1; tot = 2; e[1] = (Node){{0, 2}, 0, 2, 0}; e[2] = (Node){{0, 0}, 1, 1, 0};
	pr = 0;
	int t = read();
	for(int i = 1; i <= t; i++) {
		//printf("%d,pr at %d:", i, pr); 
		//print(rt);
		//printf("\n");
		char opt = readbc();
		if(opt == 'M') pr = read();
		else if(opt == 'I') {
			int n = read();
			for(int i = 1; i <= n; i++) s[i] = readc();
			ins(pr, n, s);
		} else if(opt == 'D') {
			int n = read();
			del(pr, n);
		} else if(opt == 'G') {
			int n = read();
			getprint(pr, n); printf("\n");
		} else if(opt == 'P')
			pr--;
		else pr++;
	}
	return 0;
}
