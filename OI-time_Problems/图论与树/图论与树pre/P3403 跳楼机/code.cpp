#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
ll h, x, y, z, ans;
ll dist[MAXN];
bool vis[MAXN];
struct QN {
	ll d; int u;
	bool operator < (const QN& b)const {return d > b.d;}
};
priority_queue<QN> pq;
void dijkstra() {
	memset(dist, 0x3f, sizeof dist);
	dist[0] = 0;
	pq.push((QN){0, 0});
	while(pq.size()) {
		int u = pq.top().u, v; pq.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		v = (u + y) % x;
		if(dist[v] > dist[u] + y) {
			dist[v] = dist[u] + y;
			pq.push((QN){dist[v], v});
		}
		v = (u + z) % x;
		if(dist[v] > dist[u] + z) {
			dist[v] = dist[u] + z;
			pq.push((QN){dist[v], v});
		}
	}
}
int main() {
	h = read(); x = read(); y = read(); z = read();
	if(x > y) swap(x, y);
	if(x > z) swap(x, z);
	dijkstra();
	for(int i = 0; i < x; i++)
		if(dist[i] <= h)
			ans += (h - dist[i] - 1) / x + 1;
	printf("%lld\n", ans);
	return 0;
}
