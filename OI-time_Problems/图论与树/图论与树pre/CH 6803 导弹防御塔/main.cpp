// http://noi-test.zzstep.com/contest/0x60%E3%80%8C%E5%9B%BE%E8%AE%BA%E3%80%8D%E4%BE%8B%E9%A2%98/6803%20%E5%AF%BC%E5%BC%B9%E9%98%B2%E5%BE%A1%E5%A1%94
/*
二分图原因：
把入侵者看成左部节点，每个防御塔的每个导弹看成右部节点（这玩意其实是个多重匹配，但是可能
同一个防御塔的各个导弹的连边可能不同，所以只能拆点来做）
那么1要素：单射满足
0要素：二分图满足
*/
#include<cstdio>
#include<cstring>
#include<cmath>
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
const int MAXN = 55;
const int MAXP = 15000;
struct Node {
    double x, y;
    friend double dist(const Node& a, const Node& b) {
        return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
    }
};
int n, m;
double T1, T2, V;
int match[MAXN][MAXN];//右边拆点
bool vis[MAXN][MAXN];
Node ivd[MAXN], dfd[MAXN];//ivd[1-m], dfd[1-n]
double mt;

bool dfs(int u) {
    for(int v = 1; v <= n; v++) {
        double t0 = dist(ivd[u], dfd[v]) / V;
        for(int k = 1; ; k++) {
            if(t0 + T1 * k + T2 * (k-1) <= mt) {
                if(!vis[v][k]) {
                    vis[v][k] = 1;
                    if(!match[v][k] || dfs(match[v][k])) {
                        match[v][k] = u;
                        return 1;
                    }
                }
            } else break;
        }
    }
    return 0;
}
bool check(double mid) {
    mt = mid;
    memset(match, 0x00, sizeof match);
    for(int i = 1; i <= m; i++) {
        memset(vis, 0x00, sizeof vis);
        if(!dfs(i)) return 0;
    }
    return 1;
}
int main() {
    n = read(), m = read();
    scanf("%lf%lf%lf", &T1, &T2, &V); T1 /= 60.0;//这个T1的问题告诉我们要认真审题
    for(int i = 1; i <= m; i++) ivd[i].x = read(), ivd[i].y = read();//left
    for(int i = 1; i <= n; i++) dfd[i].x = read(), dfd[i].y = read();//right
    double l = 0.0, r = 40000.0 / V + T1 + T2 * m / n;
    while(r - l > 1e-8) {
        double m = (l + r) / 2.0;
        if(check(m)) r = m;
        else l = m;
    }
    printf("%.6lf\n", l);
    return 0;
}