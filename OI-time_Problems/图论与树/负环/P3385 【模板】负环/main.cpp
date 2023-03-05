//https://www.luogu.com.cn/problem/P3385
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

const int MAXN = 2e3 + 5;
const int MAXM = 3e3 + 5;
int n, m;
struct Edge {
    int v, w, nxt;
}e[MAXM << 1];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int dist[MAXN];
int tot[MAXN];
bool vist[MAXN];
queue<int> q;
bool spfa() {
    memset(dist, 0x3f, sizeof dist);
    memset(tot, 0x00, sizeof tot);
    memset(vist, 0x00, sizeof vist);
    while(!q.empty()) q.pop();
    dist[1] = 0; tot[1] = 0; vist[1] = 1; q.push(1);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vist[u] = 0;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(dist[v] > dist[u] + e[i].w) {
                dist[v] = dist[u] + e[i].w;
                tot[v] = tot[u] + 1;
                if(tot[v] >= n) return 1;
                if(!vist[v]) vist[v] = 1, q.push(v);
            }
        }
    }
    return 0;
}
void work() {
    n = read(), m = read();
    memset(head, 0x00, sizeof head); cnt = 0;
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read();
        addedge(u, v, w);
        if(w >= 0) addedge(v, u, w);
    }
    if(spfa()) printf("YES\n");
    else printf("NO\n");
}
int main() {
    int T = read();
    while(T--) work();
    return 0;
}