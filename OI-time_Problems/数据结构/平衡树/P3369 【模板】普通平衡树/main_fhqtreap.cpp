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
int myrand() {
    static unsigned short sd = 10;
    sd = sd * 127 + 20;
    return sd;
}
struct FHQTreap {
    int ls[MAXN], rs[MAXN], sz[MAXN];
    int val[MAXN], key[MAXN];
    int cnt;
    int crenode(int v) {
        cnt++;
        val[cnt] = v; key[cnt] = myrand(); sz[cnt] = 1;
        ls[cnt] = rs[cnt] = 0;
    }
    void pushup(int x) {
        sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
    }
    void split(int now, int& x, int& y, int v) {
        //according to v, split now to x(<=v) and y(>y)
        if(!now) {
            x = y = 0;
            return;
        }
        if(val[now] <= v)  x = now, split(rs[now], rs[now], y, v);
            else y = now, split(ls[now], x, ls[y], v);
        pushup(now);
    }
    int merge(int x, int y) {
        //x and y have already been in the order of x(<=v) ans y(>v)
        if(!x || !y) return x + y;
        if(key[x] <= key[y]) {
            rs[x] = merge(rs[x], y);
            pushup(x);
            return x;
        } else {
            ls[y] = merge(x, ls[y]);
            pushup(y);
            return y;
        }
    }
    int ins(int& now, int v) {
        int x, y;
        split(now, x, y, v);
        now = merge(merge(x, crenode(v)), y);
    }
    int pop(int now, int v) {
        int x, y, z;
        split(now, y, z, v);
        split(y, x, y, v-1);
        now = merge(merge(x, merge(ls[y], rs[y])), z);
    }
    int rank(int now, int v) {
        int x, y;
        split(now, x, y, v-1);
        int ans = sz[x] + 1;
        now = merge(x, y);
        return ans;
    }
    int kth(int now, int k) {
        while(1) {
            if(k <= sz[ls[now]]) now = ls[now];
            else if(k <= sz[ls[now]] + 1) return val[now];
            else k -= sz[ls[now]] + 1, now = rs[now];
        }
    }
    int pre(int now, int v) {
        int x, y;
        split(now, x, y, v-1);
        int ans = kth(x, sz[x]);
        now = merge(x, y);
        return ans;
    }
    int nxt(int now, int v) {
        int x, y;
        split(now, x, y, v);
        int ans = kth(y, 1);
        now = merge(x, y);
        return ans;
    }
    FHQTreap() {
        cnt = 0;
    }
}tr;
int rt;
int main() {
    int n = read();
    while(n--) {
        int opt = read(), x = read();
        if(opt == 1) tr.ins(rt, x);
        else if(opt == 2) tr.pop(rt, x);
        else if(opt == 3) printf("%d\n", tr.rank(rt, x));
        else if(opt == 4) printf("%d\n", tr.kth(rt, x));
        else if(opt == 5) printf("%d\n", tr.pre(rt, x));
        else printf("%d\n", tr.nxt(rt, x));
    }
    return 0;
}