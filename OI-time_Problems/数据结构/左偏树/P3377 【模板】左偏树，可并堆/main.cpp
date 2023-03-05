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
const int MAXN = 1e5 + 5;
int n, m;
int ls[MAXN], rs[MAXN], val[MAXN], dis[MAXN];
int fa[MAXN];//该节点所在的最大的左偏树的树根
int getfa(int x) {return x == fa[x] ? x : fa[x] = getfa(fa[x]);}
int merge(int x, int y) {//合并x,y并把x作为根
    if(!x || !y) return x + y;
    if(val[x] > val[y] || (val[x] == val[y] && x > y)) swap(x, y);
    rs[x] = merge(rs[x], y);//把y和右子树合并
    if(dis[ls[x]] < dis[rs[x]]) swap(ls[x], rs[x]);//左偏树的性质
    fa[x] = fa[ls[x]] = fa[rs[x]] = x;
    dis[x] = dis[rs[x]] + 1;//also性质
    return x; 
}
void pop(int x) {
    val[x] = -1;
    fa[ls[x]] = ls[x];
    fa[rs[x]] = rs[x];
    fa[x] = merge(ls[x], rs[x]);
    //在路径压缩之后，必须要在pop后，给pop掉的点一个指针指向新的根（否则就会直接断掉）
    //大意就是有些点的值是直接指向fa[x]并且靠它进行一个传递，所以还是要保留
}
int main() {
    n = read(), m = read();
    dis[0] = -1;//空子树定义为-1，方便运用dis[x] = dis[rs[x]] + 1
    for(int i = 1; i <= n; i++) fa[i] = i, val[i] = read();
    for(int i = 1; i <= m; i++) {
        int opt = read();
        if(opt == 1) {
            int x = read(), y = read();
            if(val[x] == -1 || val[y] == -1) continue;
            int fx = getfa(x), fy = getfa(y);
            if(fx != fy) fa[fx] = fa[fy] = merge(fx, fy);
        } else {
            int x = read();
            if(val[x] == -1) printf("-1\n");
            else {
                int fx = getfa(x);
                printf("%d\n", val[fx]);
                pop(fx);
            }
        }
    }
    return 0;
}