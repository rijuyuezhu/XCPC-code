//http://poj.org/problem?id=1325
/*
二分图最小点覆盖原理：
2要素：一个任务（边）至少选两个模式(点）中的一个运行
显然是个二分图
*/
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
const int MAXN = 105;
const int MAXK = 1005;
int n, m, k;
struct Edge {
    int v, nxt;
}e[MAXK];
int head[MAXN], cnt;//1~n-1; 0模式一开始就是所以可以忽略
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}

int match[MAXN], ans;
bool vis[MAXN];
bool dfs(int u) {
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(vis[v]) continue;
        vis[v] = 1;
        if(!match[v] || dfs(match[v])) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}



void init() {
    fill(head + 1, head + 1 + n, 0);
    cnt = 0;
    fill(match + 1, match + 1 + m, 0);
    ans = 0;
}

void solve() {
    m = read(), k = read();
    init();
    for(int i = 1; i <= k; i++) {
        read();
        int u = read(), v = read();
        if(!u || !v) continue;
        addedge(u, v);
    }
    //konig 定理
    for(int i = 1; i <= n; i++) {
        fill(vis + 1, vis + 1 + m, 0);
        if(dfs(i)) ans++;
    }
    printf("%d\n", ans);
}
int main() {
    while(1) {
        n = read();
        if(!n) break;
        solve();
    }
    return 0;
}