//https://www.luogu.com.cn/problem/P3366
//Kruskal
#include<cstdio>
#include<algorithm>
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
int n, m;
struct Edge {
    int u, v; ll w;
}e[MAXM];
bool Edgecmp(const Edge& a, const Edge& b) {
    return a.w < b.w;
}


int upto[MAXN];
int find(int u) {
    return upto[u] == u ? u : upto[u] = find(upto[u]);
}

ll ans;
int cnt;

int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {
        e[i].u = read(), e[i].v = read(), e[i].w = read();
    }
    sort(e + 1, e + 1 + m, Edgecmp);
    for(int i = 1; i <= n; i++) upto[i] = i;
    for(int i = 1; i <= m; i++) {
        Edge& now = e[i];
        int fu = find(now.u), fv = find(now.v);
        if(fu == fv) continue;
        upto[fu] = fv;
        ans += now.w;
        cnt++;
    }
    if(cnt == n - 1) printf("%lld\n", ans);
    else printf("orz\n");
    return 0;
}