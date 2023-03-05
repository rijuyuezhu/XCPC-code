#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXM = 2e5 + 5;
char cnul[20] = "";
/*
这种插入方法。。怎么说呢
可能比较慢把

*/
struct Splay {
    int ch[MAXM][2], fa[MAXM], sz[MAXM];
    char val[MAXM][20];
    int cnt, rt;
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]

    void pushup(int x) {
        sz[x] = sz[ls(x)] + sz[rs(x)] + 1;
    }
    void linkto(int x, int y, int md) {
        fa[x] = y;
        ch[y][md] = x;
    }
    int idy(int x) {return rs(fa[x]) == x;}
    void rotate(int x) {
        int y = fa[x], z = fa[y];
        int ix = idy(x), iy = idy(y);
        int son = ch[x][ix ^ 1];
        linkto(son, y, ix);
        linkto(y, x, ix ^ 1);
        linkto(x, z, iy);
        pushup(y), pushup(x);
    }
    void splay(int x, int to) {
        while(fa[x] != to) {
            int y = fa[x];
            if(fa[y] != to) rotate(idy(x) == idy(y) ? y : x);
            rotate(x);
        }
        if(to == 0) rt = x;
    }
    int findkth(int k) {
        int now = rt;
        while(1) {
            if(k <= sz[ls(now)]) now = ls(now);
            else if( k <= sz[ls(now)] + 1) return now;
            else k -= sz[ls(now)] + 1, now = rs(now);
        }
    }
    int crenode(char v[], int f) {
        int x = ++cnt;
        ls(x) = rs(x) = 0;
        sz[x] = 1;
        fa[x] = f;
        strcpy(val[x], v);
        return x;
    }
    void insert(char v[], int k) {//ins s behind k
        int x = findkth(k), y = findkth(k + 1);
        splay(x, 0); splay(y, x);
        ls(y) = crenode(v, y);
        splay(ls(y), 0);
    }
    char* query(int k) {
        int now = findkth(k);
        return val[now];
    }
    Splay() {
        cnt = 0;
        rt = crenode(cnul, 0);
        ls(rt) = crenode(cnul, rt);
    }
    #undef ls
    #undef rs
};
Splay sp;
int n, m, q;
char name[20];
int main() {
    n = read();
    for(int i = 0; i < n; i++) {
        scanf("%s", name);
        sp.insert(name, i + 1);
    }
    m = read();
    for(int i = 1; i <= m; i++) {
        scanf("%s", name);
        int pos = read();
        sp.insert(name, pos + 1);
    }
    q = read();
    for(int i = 1; i <= q; i++) {
        int pos = read();
        printf("%s\n", sp.query(pos + 2));
    }
    return 0;
}