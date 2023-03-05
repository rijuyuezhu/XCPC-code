// https://www.luogu.com.cn/problem/P3369
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;
struct Splay {
    int fa[MAXN], ch[MAXN][2], sz[MAXN], val[MAXN], re[MAXN];
    queue<int> dustbin;
    int cnt, rt;
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]
    int crenode(int v, int f) {
        int id;
        if(dustbin.empty()) id = ++cnt;
        else id = dustbin.front(), dustbin.pop();
        fa[id] = f; ls(id) = rs(id) = 0; val[id] = v; re[id] = sz[id] = 1;
        return id;
    }
    void dty(int x) {
        dustbin.push(x);
    }
    void update(int x) {
        sz[x] = sz[ls(x)] + sz[rs(x)] + re[x];
    }
    int idy(int x) {
        return x == rs(fa[x]);
    }
    void link(int s, int f, int m) {
        fa[s] = f; ch[f][m] = s;
    }
    void rotate(int x) {
        int y = fa[x], z = fa[y];
        int ix = idy(x), iy = idy(y);
        int son = ch[x][ix ^ 1];
        link(son, y, ix);
        link(y, x, ix ^ 1);
        link(x, z, iy);
        update(y); update(x);
    }
    void splay(int x, int to) {
        while(fa[x] != to) {
            int y = fa[x];
            if(fa[y] != to) rotate(idy(x) == idy(y) ? y : x);
            rotate(x);
        }
        if(to == 0) rt = x;
    }
    void find(int v) {
        int now = rt;
        while(val[now] != v && ch[now][v > val[now]]) now = ch[now][v > val[now]];
        splay(now, 0);
    }
    void ins(int v) {
        int now = rt, fn = 0;
        while(now && val[now] != v) {
            sz[now]++;
            fn = now;
            now = ch[now][v > val[now]];
        }
        if(now) {
            re[now]++;
            splay(now, 0);
        } else {
            now = crenode(v, fn);
            if(fn) ch[fn][v > val[fn]] = now;
            splay(now, 0);
        }
    }
    int near(int v, int md) {
        find(v);
        int now = rt;
        if(md == 0 && val[now] < v) return now;
        if(md == 1 && val[now] > v) return now;
        now = ch[now][md];
        while(ch[now][md ^ 1]) now = ch[now][md ^ 1];
        return now;   
    }
    void pop(int v) {
        int l = near(v, 0), r = near(v, 1);
        splay(l, 0); splay(r, l);
        int now = ls(r);
        if(re[now] > 1) {
            re[now]--;
            splay(now, 0);
        } else {
            dty(now); ls(r) = 0;
            update(r); update(l);
        }
    }
    int rank(int v) {
        find(v);
        return sz[ls(rt)];
    }
    int kth(int k) {
        k++;
        int now = rt;
        while(1) {
            if(k <= sz[ls(now)]) now = ls(now);
            else if(k <= sz[ls(now)] + re[now]) break;
            else k -= sz[ls(now)] + re[now], now = rs(now);
        }
        splay(now, 0);
        return val[now];
    }
    int pre(int v) {
        return val[near(v, 0)];
    }
    int nxt(int v) {
        return val[near(v, 1)];
    }
    Splay() {
        cnt = 0; rt = 0;
        ins(INF); ins(-INF);
    }
    #undef ls
    #undef rs
}tr;

int main() {
    int n = read();
    while(n--) {
        int opt = read(), x = read();
        if(opt == 1) tr.ins(x);
        else if(opt == 2) tr.pop(x);
        else if(opt == 3) printf("%d\n", tr.rank(x));
        else if(opt == 4) printf("%d\n", tr.kth(x));
        else if(opt == 5) printf("%d\n", tr.pre(x));
        else printf("%d\n", tr.nxt(x));
    }    
    return 0;
}