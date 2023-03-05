// https://www.luogu.com.cn/problem/P1352
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
const int MAXN = 6e3 + 5;
int n;
int r[MAXN];
struct Edge {
    int v, nxt;
}e[MAXN];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}
int f[MAXN][2], degree[MAXN], rt;
void dp(int u) {
    f[u][0] = 0; f[u][1] = r[u];
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        dp(v);
        f[u][0] += max(f[v][1], f[v][0]);
        f[u][1] += f[v][0];
    }
}
int main() {
    n = read();
    for(int i = 1; i <= n; i++) r[i] = read();
    for(int i = 1; i < n; i++) {
        int l = read(), k = read();
        addedge(k, l); degree[l]++;
    }
    for(int i = 1; i <= n; i++) if(degree[i] == 0) rt = i;
    dp(rt);
    printf("%d\n", max(f[rt][1], f[rt][0]));
    return 0;
}