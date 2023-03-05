// https://www.luogu.com.cn/problem/P4602
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
const int MAXN = 100005;
const int MAXV = 1e5;
int n;
struct Node {
    ll d, p, l;
    bool operator < (const Node& x)const {
        return d < x.d;
    }
}a[MAXN];
struct Segment_tree {
    int ls[MAXN << 5], rs[MAXN << 5];
    ll num[MAXN << 5], sum[MAXN << 5];
    int tot;
    int update(int preo, int l, int r, int x) {//insert a[x] into the tree
        int o = ++tot;
        ls[o] = ls[preo], rs[o] = rs[preo], num[o] = num[preo], sum[o] = sum[preo];
        if(l == r) {
            num[o] += a[x].l, sum[o] += a[x].p * a[x].l;
            /*
            这里必须写上加号
            其实这相当于是一种单点修改！！！
            */
            return o;
        }
        int m = (l + r) >> 1;
        if(a[x].p <= m) ls[o] = update(ls[preo], l, m, x);
        else rs[o] = update(rs[preo], m+1, r, x);
        num[o] = num[ls[o]] + num[rs[o]];
        sum[o] = sum[ls[o]] + sum[rs[o]];
        return o;
    }
    ll query(int u, int v, int l, int r, ll k) { //the sum of 1~k in the range
        if(l == r) return k * l;
        ll numl = num[ls[v]] - num[ls[u]];
        int m = (l + r) >> 1;
        if(k <= numl) return query(ls[u], ls[v], l, m, k);
        else return sum[ls[v]] - sum[ls[u]] + query(rs[u], rs[v], m+1, r, k - numl);
    } 
}tr;
int rt[MAXN];


signed main() {
    n = read();
    int m = read();
    for(int i = 1; i <= n; i++) a[i].d = read(), a[i].p = read(), a[i].l = read();
    sort(a + 1, a + 1 + n);
    for(int i = 1; i <= n; i++) rt[i] = tr.update(rt[i-1], 1, MAXV, i);
    while(m--) {
        ll g = read(), k = read();
        int l = 1, r = n, ans = -1;
        while(l <= r) {
            int m = (l + r) >> 1;
            if(tr.num[rt[n]] - tr.num[rt[m-1]] >= k && tr.query(rt[m-1], rt[n], 1, MAXV, k) <= g) {ans = m; l = m + 1;}
            else r = m - 1;
        }
        printf("%lld\n", ans == -1 ? -1 : a[ans].d);
    }
    return 0;
}