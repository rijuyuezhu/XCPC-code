#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

constexpr int MAXN = 105;
constexpr int MAXNODE = 30005;
constexpr int MAXEDGE = 150005;
constexpr int INF = 0x3f3f3f3f;
constexpr int dx[5] = {0, 0, 0, 1, -1};
constexpr int dy[5] = {0, 1, -1, 0, 0};
const string dir = "SRLDU";
int N, S, T;
struct Edge {
    int v, nxt, w;
}e[MAXEDGE];
int cur[MAXNODE], head[MAXNODE], cnt = 1;
void addedge(int u, int v, int w) {
    e[++cnt] = {v, head[u], w}; head[u] = cnt;
    e[++cnt] = {u, head[v], 0}; head[v] = cnt;
}

int dep[MAXNODE], que[MAXNODE], hd, tl, max_flow, ans, outnumber;
string way;
bool bfs() {
    for(int i = 0; i < N; i++) {
        dep[i] = 0;
        cur[i] = head[i];
    }
    hd = 1; tl = 0;
    que[++tl] = S;
    dep[S] = 1;
    while(hd <= tl) {
        int u = que[hd++];
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(e[i].w && !dep[v]) {
                dep[v] = dep[u] + 1;
                que[++tl] = v;
                if(v == T) return 1;
            }
        }
    }
    return 0;
}
int dfs(int u, int flow) {
    if(u == T) return flow;
    int rest = flow;
    for(int &i = cur[u]; i && rest; i = e[i].nxt) {
        int v = e[i].v;
        if(e[i].w && dep[v] == dep[u] + 1) {
            int k = dfs(v, min(rest, e[i].w));
            if(!k) dep[v] = 0;
            e[i].w -= k;
            rest -= k;
            e[i^1].w += k;
        }
    }
    return flow - rest;
}

void dinic() {
    int flow;
    max_flow = 0;
    while(bfs()) {
        while(flow = dfs(S, INF))
            max_flow += flow;
    }
}

int n, a, b, sx[MAXN], sy[MAXN], ex[MAXN], ey[MAXN];

int get_num(int t, int i, int j) {
    return t * a * b + i * b + j;
}
bool legal(int x, int y) {
    return x >= 0 && y >= 0 && x < a && y < b;
}
bool check(int t) {
    N = 2 * (t+1) * a * b + 2 * n + 2;
    S = N-2;
    T = N-1;
    for(int i = 0; i < N; i++)
        head[i] = 0;
    cnt = 1;
    for(int i = 1; i <= n; i++)
        addedge(S, get_num(0, sx[i], sy[i]), 1);
    for(int i = 0; i < (t+1) * a * b; i++)
        addedge(i, i + (t+1) * a * b, 1);
    for(int i = 1; i <= n; i++)
        for(int k = 0; k <= t; k++)
            addedge((t+1) * a * b + get_num(k, ex[i], ey[i]), 2 * (t+1) * a * b + i-1, 1);
    for(int i = 1; i <= n; i++) {
        addedge(2 * (t+1) * a * b + i-1, 2 * (t+1) * a * b + n + i-1, 1);
        addedge(2 * (t+1) * a * b + n + i-1, T, 1);
    }
    for(int k = 0; k < t; k++)
        for(int x = 0; x < a; x++)
            for(int y = 0; y < b; y++)
                for(int d = 0; d < 5; d++) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if(!legal(nx, ny))
                        continue;
                    addedge((t+1) * a * b + get_num(k, x, y), get_num(k+1, nx, ny), 1);
                }
    dinic();
    return max_flow == n;
}

void getway(int x, int y) {
    way.clear();
    outnumber = 0;
    int t = 0;
    while(1) {
        int pos = get_num(t, x, y) + (ans+1) * a * b;
        for(int i = head[pos]; i; i = e[i].nxt)
            if(e[i^1].w == 1) {
                int v = e[i].v;
                if(v < (ans+1) * a * b) {
                    //case 1, next layer
                    int vx = v % (a * b) / b, vy = v % (a * b) % b;
                    for(int k = 0; k < 5; k++)
                        if(vx == x + dx[k] && vy == y + dy[k]) {
                            way += dir[k];
                            x = vx;
                            y = vy;
                            t++;
                            break;
                        }
                } else {
                    //case 2, outside
                    outnumber = v - 2 * (ans+1) * a * b + 1;
                    return ;
                }
            }
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> a >> b;
    for(int i = 1; i <= n; i++) {
        cin >> sx[i] >> sy[i];
        sx[i]--; sy[i]--;
    }
    for(int i = 1; i <= n; i++) {
        cin >> ex[i] >> ey[i];
        ex[i]--; ey[i]--;
    }
    int L = 1, R = a * b;
    ans = -1;
    while(L <= R) {
        int M = (L + R) >> 1;
        if(check(M)) {
            ans = M;
            R = M - 1;
        } else
            L = M + 1;
    }
    check(ans);
    cout << ans << '\n';
    for(int i = 1; i <= n; i++) {
        getway(sx[i], sy[i]);//retrun way, outnumber
        cout << sx[i]+1 << ' ' << sy[i]+1 << ' ' << ex[outnumber]+1 << ' ' << ey[outnumber]+1 << ' ' << way;
        for(int i = way.length(); i < ans; i++)
            cout << 'P';
        cout << '\n';
    }
    return 0;
}
