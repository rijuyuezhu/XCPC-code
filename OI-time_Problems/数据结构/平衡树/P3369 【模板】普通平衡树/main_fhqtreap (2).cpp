#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
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
const int MAXN = 1e5 + 5;
namespace FHQTreap {
	struct Node {
		int ls, rs;
		int v, k, s;
	}e[MAXN];
	int cnt;
	void upd(int x) {e[x].s = e[e[x].ls].s + e[e[x].rs].s + 1;}
	int crenode(int v) {
		e[++cnt] = (Node){0, 0, v, rand(), 1};
		return cnt;
	}
	void split(int now, int& x, int& y, int v) {
		if(!now) {x = y = 0; return;}
		if(e[now].v <= v) 
			x = now, split(e[now].rs, e[x].rs, y, v), upd(x);
		else
			y = now, split(e[now].ls, x, e[y].ls, v), upd(y);
	}
	int merge(int x, int y) {
		if(!x || !y) return x | y;
		if(e[x].k < e[y].k)
			return e[x].rs = merge(e[x].rs, y), upd(x), x;
		else
			return e[y].ls = merge(x, e[y].ls), upd(y), y;
	}
	int kth(int x, int k) {
		while(1) {
			if(k <= e[e[x].ls].s) x = e[x].ls;
			else {
				k -= e[e[x].ls].s + 1;
				if(!k) return x;
				x = e[x].rs;
			}
		}
	}
	void ins(int& now, int v) {
		int x, y;
		split(now, x, y, v);
		now = merge(merge(x, crenode(v)), y);
	}
	void del(int& now, int v) {
		int x, y, z;
		split(now, x, y, v-1); split(y, y, z, v);
		y = merge(e[y].ls, e[y].rs);
		now = merge(merge(x, y), z);
	}
	int rk(int& now, int v) {
		int x, y;
		split(now, x, y, v-1);
		int ans = e[x].s + 1;
		now = merge(x, y);
		return ans;
	}
	int atrank(int& now, int k) {
		return e[kth(now, k)].v;
	}
	int pre(int& now, int v) {
		int x, y;
		split(now, x, y, v-1);
		int ans = e[kth(x, e[x].s)].v;
		now = merge(x, y);
		return ans;
	}
	int nxt(int& now, int v) {
		int x, y;
		split(now, x, y, v);
		int ans = e[kth(y, 1)].v;
		now = merge(x, y);
		return ans;
	}
}
using namespace FHQTreap;
int rt;
int main() {
	rt = 0;
    int n = read();
    while(n--) {
        int opt = read(), x = read();
        if(opt == 1) ins(rt, x);
        else if(opt == 2) del(rt, x);
        else if(opt == 3) printf("%d\n", rk(rt, x));
        else if(opt == 4) printf("%d\n", atrank(rt, x));
        else if(opt == 5) printf("%d\n", pre(rt, x));
        else printf("%d\n", nxt(rt, x));
    }	
	return 0;
}
