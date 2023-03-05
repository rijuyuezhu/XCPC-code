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
const int MAXN = 55;
int n, num;
int stu[MAXN], gohome[MAXN];
struct Edge {
    int v, nxt;
}e[MAXN * MAXN * 2];
int head[MAXN], cnt;
void addedge(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}

int match[MAXN], vis[MAXN];

bool dfs(int u) {
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if(!vis[v]) {
            vis[v] = 1;
            if(!match[v] || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
void work() {
    memset(head, 0x00, sizeof head);
    cnt = 0; num = 0;
    n = read();
    for(int i = 1; i <= n; i++) stu[i] = read();
    for(int i = 1; i <= n; i++) gohome[i] = read();
    for(int i = 1; i <= n; i++)
        if(stu[i] && !gohome[i])
            addedge(i, i);
    for(int i = 1; i <= n; i++)
        if(!stu[i] || (stu[i] && !gohome[i])) num++;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
            int t = read();
            if(t && stu[j]) addedge(i, j);
        }
    memset(match, 0x00, sizeof match);
    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(!stu[i] || (stu[i] && !gohome[i])) {
            memset(vis, 0x00, sizeof vis);
            if(dfs(i)) ans++;
        }
    if(ans == num) printf("^_^\n");
    else printf("T_T\n");
}
int main() {
    int T = read();
    while(T--) work();
    return 0;
}