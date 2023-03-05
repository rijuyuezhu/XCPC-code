#include<cstdio>
#include<cstring>
#include<algorithm>
#include<deque>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 50005;
const int pINF = 0xc1c1c1c1;
int n;
struct Edge {
    int v, nxt, w;
}e[MAXN << 2];
int head[MAXN], cnt;
void addedge(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}

deque<int> dq;
int inq[MAXN], dist[MAXN];
void work() {
    memset(head, 0x00, sizeof head); cnt = 0;
    n = read();
    for(int i = 1; i <= n; i++) {
        int a = read(), b = read(), c = read();
        addedge(a, b + 1, c);
    } 
    for(int i = 0; i < 50000; i++) {
        addedge(i, i+1, 0);
        addedge(i+1, i, -1);
    }
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;
    dq.push_back(0); inq[0] = 1;
    while(!dq.empty()) {
        int u = dq.front(); dq.pop_front(); inq[u] = 0;
        for(int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if(dist[v] < dist[u] + e[i].w) {
                dist[v] = dist[u] + e[i].w;
                if(!inq[v]) {
                    inq[v] = 1;
                    if(!dq.empty() && dist[v] > dist[dq.front()]) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }
    }
    printf("%d\n", dist[50000]);
    
}
int main() {
    int T = read();
    while(T--) work();
    return 0;
}