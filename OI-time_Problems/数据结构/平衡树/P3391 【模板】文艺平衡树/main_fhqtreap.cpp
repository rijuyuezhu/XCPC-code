#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
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
struct FHQTreap {
    int sz[MAXN], ls[MAXN], rs[MAXN];
    int key[MAXN], val[MAXN];
    int tag[MAXN];
    int cnt;
    int crenode(int v) {
        cnt++;
        val[cnt] = v;
        key[cnt] = rand();
        sz[cnt] = 1;
        ls[cnt] = rs[cnt] = 0;
        tag[cnt] = 0;
        return cnt;
    }
    void pushup(int x) {
        sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
    }
    void pushdown(int x) {
        if(tag[x]) {
            swap(ls[x], rs[x]);
            if(ls[x]) tag[ls[x]] ^= 1;
            if(rs[x]) tag[rs[x]] ^= 1;
            tag[x] = 0;
        }
    }
    void split(int now, int& x, int& y, int k) {
        if(!now) x = y = 0;
        else {
            pushdown(now);
            if(sz[ls[now]] + 1 <= k)
                x = now, split(rs[now], rs[x], y, k - sz[ls[now]] - 1);
            else y = now, split(ls[now], x, ls[y], k);
            pushup(now);
        }
    }
    int merge(int x, int y) {
        if(!x || !y) return x | y;
        if(key[x] <= key[y]) {
            pushdown(x);
            rs[x] = merge(rs[x], y);
            pushup(x);
            return x;
        } else {
            pushdown(y);
            ls[y] = merge(x, ls[y]);
            pushup(y);
            return y;
        }
    }
    void reverse(int& now, int l, int r) {
        int x, y, z;
        split(now, y, z, r);
        split(y, x, y, l - 1);
        tag[y] ^= 1;
        now = merge(merge(x, y), z);
    }
    void print(int now) {
        if(!now) return;
        pushdown(now);
        print(ls[now]);
        printf("%d ", val[now]);
        print(rs[now]);
    }
    FHQTreap() {
        cnt = 0;
    }
}tr;
int rt;
int n, m;
int main() {
    srand(time(0));
    n = read(), m = read();  
    rt = 0;
    for(int i = 1; i <= n; i++) rt = tr.merge(rt, tr.crenode(i));
    for(int i = 1; i <= m; i++) {
        int l = read(), r = read();
        tr.reverse(rt, l, r);
    }
    tr.print(rt);
    return 0;
}