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
const int MAXN = 100005;
namespace LeftistTree {
    int ch[MAXN][2];
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]
    int val[MAXN];
    int dis[MAXN];
    int fa[MAXN];
    int cnt;
    void init() {
        cnt = 0; dis[0] = -1;
    }
    int getfa(int x) {return x == fa[x] ? x : fa[x] = getfa(fa[x]);}
    int crenode(int v) {
        cnt++;
        val[cnt] = v;
        ls(cnt) = rs(cnt) = 0;
        dis[cnt] = 0;
        fa[cnt] = cnt;
        return cnt;
    }
    int merge(int x, int y) {
        if(!x || !y) return x + y;
        if(val[x] < val[y]) swap(x, y);
        rs(x) = merge(rs(x), y);
        if(dis[ls(x)] < dis[rs(x)]) swap(ls(x), rs(x));
        dis[x] = dis[rs(x)] + 1;
        fa[x] = fa[ls(x)] = fa[rs(x)] = x;
        return x;
    }
}
using namespace LeftistTree;
int n;
int m;
void fight(int x, int y) {
    x = getfa(x), y = getfa(y);
    if(x == y) {
        printf("-1\n");
        return;
    }
    val[x] /= 2;
    int rtx = merge(ls(x), rs(x));
    ls(x) = rs(x) = dis[x] = 0;
    fa[x] = merge(rtx, x); x = getfa(x);
    val[y] /= 2;
    int rty = merge(ls(y), rs(y));
    ls(y) = rs(y) = dis[y] = 0;
    fa[y] = merge(rty, y); y = getfa(y);
    fa[x] = fa[y] = merge(x, y);
    printf("%d\n", val[fa[x]]);
}
int main() {
    while(scanf("%d", &n) != EOF) {
        init();
        for(int i = 1; i <= n; i++) crenode(read());
        m = read();
        while(m--) {
            int x = read(), y = read();
            fight(x, y);
        }
    }
    return 0;
}