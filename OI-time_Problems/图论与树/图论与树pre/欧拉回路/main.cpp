// https://uoj.ac/problem/117
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
const int MAXN = 1e5 + 5, MAXM = 2e5 + 5;
int t, n, m;
struct Edge {
    int v, nxt, id;
}e[MAXM << 1];
int head[MAXN], cnt;
void addedge(int u, int v, int id) {
    e[++cnt].v = v; e[cnt].id = id; e[cnt].nxt = head[u]; head[u] = cnt;
}
int indeg[MAXN], outdeg[MAXN];
int main() {
    t = read();
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        int u = read(), v = read();
        addedge(u, v, i);
        if(t == 1) addedge(v, u, -i);
        
    }
    return 0;
}