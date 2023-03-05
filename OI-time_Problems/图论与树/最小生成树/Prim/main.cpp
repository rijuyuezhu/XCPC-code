//https://www.luogu.com.cn/problem/P3366
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 5005;
const int MAXM = 2e5 + 5;
const int INF = 0x3f3f3f3f;
int n, m;
struct Edge {
    int v, nxt, w;
}e[MAXM << 1];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > pq;
bool vist[MAXN];
int dist[MAXN];
int ans;
int tot;


int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read(), w = read();
        addedge(u, v, w);
        addedge(v, u, w);
    }
    tot = 0, ans = 0;
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0; pq.push(pii(0, 1));
    while(!pq.empty()) {
        int u = pq.top().second; pq.pop();
        if(vist[u]) continue;
        vist[u] = 1;
        tot++; ans += dist[u];
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v, w = e[i].w;
            if(!vist[v] && dist[v] > e[i].w) {
                dist[v] = e[i].w;
                pq.push(pii(dist[v],v));
            }
        }
    }
    if(tot == n) printf("%d\n", ans);
    else printf("orz\n");
    return 0;
}