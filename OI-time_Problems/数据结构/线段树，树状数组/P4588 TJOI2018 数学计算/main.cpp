#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXQ = 100005;
ll q, mod;
struct Segtree {
    #define ls o << 1
    #define rs o << 1 | 1
    ll val[MAXQ << 2];//我又sb没开2倍！！！
    void pushup(int o) {
        val[o] = val[ls] * val[rs] % mod;
    }
    void build(int o, int l, int r) {
        if(l == r) {
            val[o] = 1;
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m);
        build(rs, m + 1, r);
        pushup(o);
    }
    void mdy(int o, int l, int r, int x, ll k) {
        if(l == r) {
            val[o] = k;
            return; 
        }
        int m = (l + r) >> 1;
        if(x <= m) mdy(ls, l, m, x, k);
        else mdy(rs, m + 1, r, x, k);
        pushup(o);
    }
    #undef ls
    #undef rs

};
Segtree tr;
void work() {
    q = read(), mod = read();
    tr.build(1, 1, q);
    for(int i = 1; i <= q; i++) {
        int opt = read();
        if(opt == 1) {
            tr.mdy(1, 1, q, i, read() % mod);
        } else {
            tr.mdy(1, 1, q, read(), 1);
        }
        printf("%lld\n", tr.val[1]);
    }
}
int main() {
    int t = read();
    while(t--) work();
    return 0;
}
