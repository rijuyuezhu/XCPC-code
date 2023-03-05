//https://www.luogu.com.cn/problem/P2713
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
const int MAXN = 1000005;
const int INF = 0x3f3f3f3f;
namespace Leftist_Tree {
    int ch[MAXN][2];
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]
    int dis[MAXN];
    int val[MAXN];//if deleted, val = INF
    int fa[MAXN];
    int cnt;
    void init() {
        cnt = 0;
        dis[0] = -1;
    }
    int crenode(int v) {
        cnt++;
        ls(cnt) = rs(cnt) = 0;
        val[cnt] = v;
        fa[cnt] = cnt;
        dis[cnt] = 0;
        return cnt;
    }
    int getfa(int x) {
        return x == fa[x] ? x : fa[x] = getfa(fa[x]);
    }
    int merge(int x, int y) {
        if(!x || !y) return x + y;
        if(val[x] > val[y]) swap(x, y);
        rs(x) = merge(rs(x), y);
        if(dis[ls(x)] < dis[rs(x)]) swap(ls(x), rs(x));
        dis[x] = dis[rs(x)] + 1;
        fa[x] = fa[ls(x)] = fa[rs(x)] = x;
        return x;
    }
    void del(int x) {
        val[x] = INF;
        fa[ls(x)] = ls(x); fa[rs(x)] = rs(x);
        fa[x] = merge(ls(x), rs(x));
    }

}
using namespace Leftist_Tree;
int n, m;
int main() {
    n = read();
    init();
    for(int i = 1; i <= n; i++) {
        int p = read();
        crenode(p);
    }
    m = read();
    while(m--) {
        char op[5];
        scanf("%s", op);
        if(op[0] == 'M') {
            int x = read(), y = read();
            if(val[x] == INF || val[y] == INF) continue;
            x = getfa(x), y = getfa(y);
            if(x != y) merge(x, y);//一定要判断是否在一个堆中！！！
        } else {
            int x = read();
            if(val[x] == INF) printf("0\n");
            else {
                x = getfa(x);
                printf("%d\n", val[x]);
                del(x);
            }
        }
    }
    return 0;
}