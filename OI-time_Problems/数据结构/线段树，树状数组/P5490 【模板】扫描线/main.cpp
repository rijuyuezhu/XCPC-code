#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 2e5 + 5;
int n;
struct Node {
    int x, y1, y2, w;
    Node() {}
    Node(int x, int y1, int y2, int w) : x(x), y1(y1), y2(y2), w(w) {}
    bool operator < (const Node& b)const {
        return x < b.x;
    }
}t[MAXN << 1];
int cnt;
ll lsh[MAXN << 1], tot;
void LSH() {
    sort(lsh + 1, lsh + 1 + tot);
    tot = unique(lsh + 1, lsh + 1 + tot) - lsh - 1;
}
int LSH(ll x) {
    return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;
}
struct Segtree {
    ll cnt[MAXN << 3];
    ll len[MAXN << 3];
    #define ls o << 1
    #define rs o << 1 | 1
    void pushup(int o, int l, int r) {
        if(cnt[o]) len[o] = lsh[r + 1] - lsh[l];
        else if(l == r) len[o] = 0;
        else len[o] = len[ls] + len[rs];
    }
    void addr(int o, int l, int r, int x, int y, ll k) {
        if(x <= l && r <= y) {
            cnt[o] += k;
            pushup(o, l, r);
            return;
        }
        int m = (l + r) >> 1;
        if(x <= m) addr(ls, l, m, x, y, k);
        if(y > m) addr(rs, m + 1, r, x, y, k);
        pushup(o, l, r);
    }
    #undef ls
    #undef rs
};
ll ans;
Segtree tr;
int main() {
    n = read();
    for(int i = 1; i <= n; i++) {
        int x1 = read(), y1 = read(), x2 = read(), y2 = read();
        lsh[++tot] = y1; lsh[++tot] = y2;
        t[++cnt] = Node(x1, y1, y2, 1);
        t[++cnt] = Node(x2, y1, y2, -1);
    }
    LSH();
    sort(t + 1, t + 1 + cnt);
    for(int i = 1; i < cnt; i++) {
        Node& now = t[i];
        int y1 = LSH(now.y1), y2 = LSH(now.y2);
        tr.addr(1, 1, tot - 1, y1, y2 - 1, now.w);
        ans += (t[i + 1].x - t[i].x) * tr.len[1];
    }
    printf("%lld\n", ans);
    return 0;
}