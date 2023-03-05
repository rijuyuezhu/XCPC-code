//https://www.luogu.com.cn/problem/P3369
#include<cstdio>
#include<queue>
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
/*
注意事项：
由于本树空的话会出事(特别是求前驱后继的时候)
所以应该插入+-INF
那么kth和rank要注意一下细节
ok~
愉快的splay
*/
struct Splay {
    int ch[MAXN][2], fa[MAXN], val[MAXN], sz[MAXN], re[MAXN];
    int cnt;
    int rt;
    queue<int> dustbin;
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]
    int crenode(int v, int f) {
        int num;
        if(!dustbin.empty()) {num = dustbin.front(); dustbin.pop();}
        else num = ++cnt;
        ls(num) = rs(num) = 0;
        fa[num] = f;
        sz[num] = re[num] = 1;
        val[num] = v;
        return num;
    }
    void dty(int x) {
        dustbin.push(x);
    }
    void pushup(int x) {
        if(x) sz[x] = sz[ls(x)] + sz[rs(x)] + re[x];
    }
    void linkto(int x, int y, int md) {//let x become y's ch[y][md]
        fa[x] = y;
        ch[y][md] = x;
    }
    int idt(int x) {// return x is fa[x] 's leftson[=0] or rightson[=1]
        return rs(fa[x]) == x;
    }
    void rotate(int x) {
        int y = fa[x], z = fa[y];
        int ix = idt(x), iy = idt(y);
        int son = ch[x][ix ^ 1];
        linkto(son, y, ix);
        linkto(y, x, ix ^ 1);
        linkto(x, z, iy);
        pushup(y); pushup(x);
    }
    void splay(int x, int to) {
        while(fa[x] != to) {
            int y = fa[x];
            if(fa[y] != to) rotate(idt(x) == idt(y) ? y : x);
            rotate(x);
        }
        if(to == 0) rt = x;
    }
    void find(int v) { //find node whose val is v, and splay it to the rt
        int now = rt;
        while(val[now] != v && ch[now][v > val[now]]) now = ch[now][v > val[now]];
        splay(now, 0);
    }
    void ins(int v) {
        int now = rt, fn = 0;
        while(val[now] != v && now) {
            sz[now]++;
            fn = now;
            now = ch[now][v > val[now]];
        }
        if(val[now] == v) {
            re[now]++;
            splay(now, 0);
        } else {
            now = crenode(v, fn);
            if(fn != 0) ch[fn][v > val[fn]] = now;
            splay(now, 0);
        }
    }
    int near(int v, int md) {//md: pre[=0]; nxt[=1] return the num of the node
        find(v);
        int now = rt;
        if(md == 0 && val[now] < v) return now;
        if(md == 1 && val[now] > v) return now;
        now = ch[now][md];
        while(ch[now][md ^ 1]) now = ch[now][md ^ 1];
        return now;
    }
    void del(int v) {
        int l = near(v, 0), r = near(v, 1);
        splay(l, 0); splay(r, l);
        int now = ls(r);
        if(!now) return;
        if(re[now] > 1) {
            re[now]--;
            splay(now, 0);
        } else {
            dty(now);
            ls(r) = 0;
            splay(r, 0);
        }
    }
    int rank(int v) {
        find(v);
        return sz[ls(rt)] + 1;
    }
    int kth(int k) {
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
    #undef ls
    #undef rs
};
int n;
Splay sp;
int main() {
    sp.ins(INF); sp.ins(-INF);
    n = read();
    while(n--) {
        int opt = read();
        switch(opt) {
            case 1:
                sp.ins(read());
                break;
            case 2:
                sp.del(read());
                break;
            case 3:
                printf("%d\n", sp.rank(read()) - 1);
                break;
            case 4:
                printf("%d\n", sp.kth(read() + 1));
                break;
            case 5:
                printf("%d\n", sp.pre(read()));
                break;
            case 6:
                printf("%d\n", sp.nxt(read()));
        }
    }
    return 0;
}