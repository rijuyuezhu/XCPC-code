// https://www.luogu.com.cn/problem/CF920F
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
const int MAXN = 3e5 + 5;
const int MAXV = 1e6 + 5;
int d[MAXV], a[MAXV], notprime[MAXV], prime[MAXV], cnt;
void calc() {
    notprime[1] = 1, d[1] = 1, a[1] = 0;
    for(int i = 2; i < MAXV; i++) {
        if(!notprime[i]) {
            prime[++cnt] = i;
            d[i] = 2; a[i] = 1;
        }
        for(int j = 1; j <= cnt && i * prime[j] < MAXV; j++) {
            notprime[i * prime[j]] = 1;
            if(i % prime[j] == 0) {//i*p[j] have over 1 p[j]
                d[i * prime[j]] = d[i] / (a[i] + 1) * (a[i] + 2), a[i * prime[j]] = a[i] + 1;
                break;
            } else d[i * prime[j]] = d[i] * d[prime[j]], a[i * prime[j]] = 1;//i*p[j] have only one p[j]
        }
    }
}
struct Segment_tree {
    #define ls (o << 1)
    #define rs (o << 1 | 1)
    ll sum[MAXN << 2]; bool flag[MAXN << 2];
    void pushup(int o) {
        sum[o] = sum[ls] + sum[rs];
        flag[o] = flag[ls] && flag[rs];
    }
    void build(int o, int l, int r, ll a[]) {
        if(l == r) {
            sum[o] = a[l];
            flag[o] = (a[l] <= 2);
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m, a); build(rs, m+1, r, a);
        pushup(o);
    }
    void mdyrange(int o, int l, int r, int x, int y) {
        if(flag[o]) return;
        if(l == r) {
            sum[o] = d[sum[o]];
            if(sum[o] <= 2) flag[o] = 1;
            return;
        }
        int m = (l + r) >> 1;
        if(x <= m) mdyrange(ls, l, m, x, y);
        if(y > m) mdyrange(rs, m+1, r, x, y);
        pushup(o);
    }
    ll query(int o, int l, int r, int x, int y) {
        if(x <= l && r <= y) return sum[o];
        int m = (l + r) >> 1;
        if(y <= m) return query(ls, l, m, x, y);
        else if(x > m) return query(rs, m+1, r, x, y);
        else return query(ls, l, m, x, y) + query(rs, m+1, r, x, y);
    }
    #undef ls
    #undef rs
}tr;
int n, m;
ll v[MAXN];
int main() {
    calc();
    n = read(), m = read();
    for(int i = 1; i <= n; i++) v[i] = read();
    tr.build(1, 1, n, v);
    while(m--) {
        int t = read(), l = read(), r = read();
        if(t == 1) tr.mdyrange(1, 1, n, l, r);
            else printf("%lld\n", tr.query(1, 1, n, l, r));
    }
    return 0;
}