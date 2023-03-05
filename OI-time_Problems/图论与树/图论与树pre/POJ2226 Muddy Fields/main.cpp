// http://poj.org/problem?id=2226
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
char readc() {
    char ch = getchar();
    while(ch != '*' && ch != '.') ch = getchar();
    return ch;
}
const int MAXN = 55;
int n, m, mud[MAXN][MAXN], beln[MAXN][MAXN], ggn, belm[MAXN][MAXN], ggm;
struct Edge {
    int v, nxt;
}e[MAXN * MAXN];
int head[MAXN * MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}
int match[MAXN * MAXN], ans;
bool vis[MAXN * MAXN];
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
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            mud[i][j] = (readc() == '*');
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) 
            if(mud[i][j]) {
                beln[i][j] = (mud[i][j-1] ? beln[i][j-1] : ++ggn);
                belm[i][j] = (mud[i-1][j] ? belm[i-1][j] : ++ggm);
                addedge(beln[i][j], belm[i][j]);
            }
    for(int i = 1; i <= ggn; i++) {
        fill(vis + 1, vis + 1 + ggm, 0);
        if(dfs(i)) ans++;
    }
    printf("%d\n", ans);
    return 0;
}