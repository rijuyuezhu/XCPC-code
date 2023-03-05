// https://www.luogu.com.cn/problem/P4587
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
const int INF = 1e9;
int n;
int a[MAXN];

struct Segment_tree {
    int ls[MAXN << 5], rs[MAXN << 5];
    int val[MAXN << 5];
    int rt[MAXN];
    int tot;
    int update(int preo, int l, int r, int x, int v) {
        int o = ++tot;
        ls[o] = ls[preo]; rs[o] = rs[preo]; val[o] = val[preo] + v;
        if(l == r) return o;
        int m = (l + r) >> 1;
        if(x <= m) ls[o] = update(ls[preo], l, m, x, v);
        else rs[o] = update(rs[preo], m+1, r, x, v);
        return o;
    }
    int query(int u, int v, int l, int r, int x, int y) {
        if(x <= l && r <= y) return val[v] - val[u];
        int m = (l + r) >> 1, ans = 0;
        if(x <= m) ans += query(ls[u], ls[v], l, m, x, y);
        if(y > m) ans += query(rs[u], rs[v], m+1, r, x, y);
        return ans;
    }
}tr;
int main() {
    n = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    for(int i = 1; i <= n; i++) tr.rt[i] = tr.update(tr.rt[i-1], 1, INF, a[i], a[i]);
    int m = read();
    while(m--) {
        int l = read(), r = read(), ans = 1;
        while(1) {
            int ret = tr.query(tr.rt[l-1], tr.rt[r], 1, INF, 1, ans);
            if(ans <= ret) ans = ret + 1;
            else break;
        }
        printf("%d\n", ans);
    }
    return 0;
}