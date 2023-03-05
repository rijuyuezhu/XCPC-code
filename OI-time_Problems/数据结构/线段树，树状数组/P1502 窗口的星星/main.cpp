#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 1e4 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, w, h;
struct Node {
    int y, x1, x2; ll l;
    Node() {}
    Node(int y, int x1, int x2, ll l) : y(y), x1(x1), x2(x2), l(l) {}
    bool operator < (const Node& b)const {
        if(y != b.y) return y < b.y;
        return l > b.l;
    }
    /*
    此处排序给我长个心眼了！
    这不是算面积
    我们要求最大的值
    那么
    在y相同时我们应该先全部把正权值加上（这点的完成）
    再减去所有的负权值（下个点的预备）
    在排序上就是y相同时按l降序排序
    */
}t[MAXN << 1];
ll lsh[MAXN << 1]; int idl;
void LSH() {
    sort(lsh + 1, lsh + 1 + idl);
    idl = unique(lsh + 1, lsh + 1 + idl) - lsh - 1;
}
int LSH(ll x) {
    return lower_bound(lsh + 1, lsh + 1 + idl, x) - lsh;
}
struct Segtree {
    #define ls o << 1
    #define rs o << 1 | 1
    ll val[MAXN << 3];
    ll tag[MAXN << 3];
    void pushup(int o) {
        val[o] = max(val[ls], val[rs]);
    }
    void addp(int o, ll k) {
        val[o] += k;
        tag[o] += k;
    }
    void pushdown(int o) {
        if(tag[o]) {
            addp(ls, tag[o]);
            addp(rs, tag[o]);
            tag[o] = 0;
        }
    }
    void addr(int o, int l, int r, int x, int y, ll k) {
        if(x <= l && r <= y) {
            addp(o, k);
            return;
        }
        pushdown(o);
        int m = (l + r) >> 1;
        if(x <= m) addr(ls, l, m, x, y, k);
        if(y > m) addr(rs, m + 1, r, x, y, k);
        pushup(o);
    }
    #undef ls
    #undef rs  
};
Segtree tr;
ll ans;
void work() {
    n = read(), w = read(), h = read();
    idl = 0;
    for(int i = 1; i <= n; i++) {
        int x = read(), y = read(); ll l = read();
        t[2 * i - 1] = Node(y - h + 1, x - w + 1, x, l);
        t[2 * i] = Node(y, x - w + 1, x, -l);
        lsh[++idl] = x - w + 1; lsh[++idl] = x;
    }
    LSH();
    n <<= 1;
    sort(t + 1, t + 1 + n);
    ans = -INF;
    for(int i = 1; i <= n; i++) {
        Node now = t[i];
        now.x1 = LSH(now.x1), now.x2 = LSH(now.x2);
        tr.addr(1, 1, n, now.x1, now.x2, now.l);
        ans = max(ans, tr.val[1]);
    }
    printf("%lld\n", ans);
}
int main() {
    int T = read();
    while(T--) work();
    return 0;
}