// https://www.luogu.com.cn/problem/P3701
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
enum person {
    J = 0, HK = 1, W = 2, YYY = 3, E = 4
};
const int MAXN = 210;
const int INF = 5e8;
const int table[5][5] = {//这个表绝对不能打错！！！
    {0, 1, 1, 0, 0},
    {0, 0, 1, 0, 1},
    {0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0},
    {1, 0, 0, 1, 0}
};
int readtype() {
    char s[10];
    scanf("%s", s);
    switch(s[0]) {
        case 'J': return J;
        case 'H': return HK;
        case 'W': return W;
        case 'Y': return YYY;
        case 'E': return E;
    }
    return -1;
}
int n, m;
int ty1[MAXN], hth1[MAXN], ty2[MAXN], hth2[MAXN];

int s, t;
struct Edge {
    int v, w, nxt;
}e[100005];
int head[MAXN], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
    e[++cnt].v = u; e[cnt].w = 0; e[cnt].nxt = head[v]; head[v] = cnt;
}

int d[MAXN];
bool bfs() {
    memset(d, 0x00, sizeof d);
    queue<int> q;
    q.push(s), d[s] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(!d[v] && e[i].w) {
                d[v] = d[u] + 1;
                q.push(v);
                if(v == t) return 1;
            }
        }
    }
    return 0;
}
int dfs(int u, int flow) {
    if(u == t) return flow;
    int rest = flow;
    for(int i = head[u]; i && rest; i = e[i].nxt) {
        int v = e[i].v;
        if(d[v] == d[u] + 1 && e[i].w) {
            int k = dfs(v, min(rest, e[i].w));
            if(!k) d[v] = 0;
            rest -= k;
            e[i].w -= k;
            e[i^1].w += k;
        }
    }
    return flow - rest;
}
int dinic() {
    int flow, ans = 0;
    while(bfs())
        while(flow = dfs(s, INF)) ans += flow;
    return ans;
}
int main() {
    n = read(), m = read();


    int numy1 = 0, numy2 = 0;
    for(int i = 1; i <= n; i++) {
        ty1[i] = readtype();
        if(ty1[i] == YYY) numy1++;
    }
    for(int i = 1; i <= n; i++) {
        ty2[i] = readtype();
        if(ty2[i] == YYY) numy2++;
    }
    for(int i = 1; i <= n; i++) {
        hth1[i] = read();
        if(ty1[i] == J) hth1[i] += numy1;
    }
        
    for(int i = 1; i <= n; i++) {
        hth2[i] = read();
        if(ty2[i] == J) hth2[i] += numy2;
    }
    /*
    byx:1~n
    snj:n+1~2n
    s:2n+1
    t:2n+2
    */
    s = 2 * n + 1; t = 2 * n + 2;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(table[ty1[i]][ty2[j]]) addedge(i, j + n, 1);//只能打一架
    for(int i = 1; i <= n; i++) addedge(s, i, hth1[i]);
    for(int i = 1; i <= n; i++) addedge(i + n, t, hth2[i]);
    
    printf("%d\n", min(m, dinic()));
    return 0;
}