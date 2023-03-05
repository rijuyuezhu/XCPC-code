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
int n, m, k;
ll p, h[MAXN], a[MAXN], ans, l, r, cnt[MAXN];
struct Node {
	ll d; int u;
	Node(ll d = 0, int u = 0) : d(d), u(u) {}
};
bool operator < (const Node& a, const Node& b) {return a.d > b.d;}
priority_queue<Node> que;
bool check(ll lim) {
	que = priority_queue<Node>();
	for(int i = 1; i <= n; i++) {
		cnt[i] = 0;
		if(lim - m * a[i] < h[i])
			que.push(Node(lim / a[i] + 1, i));
	}
	for(int i = 1; i <= m && que.size(); i++)
		for(int j = 1; j <= k && que.size(); j++) {
			Node t = que.top(); que.pop();
			if(t.d <= i) return 0;
			cnt[t.u]++;
			if(lim + cnt[t.u] * p - m * a[t.u] < h[t.u])
				que.push(Node((lim + cnt[t.u] * p) / a[t.u] + 1, t.u));
		}
	return que.empty();
}

int main() {
	n = read(), m = read(), k = read(), p = read();
	l = -INF; r = -INF;
	for(int i = 1; i <= n; i++) {
		h[i] = read(), a[i] = read();
		l = max(l, a[i]); r = max(r, h[i] + m * a[i]);
	}
	while(l <= r) {
		ll mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%lld\n", ans);
	return 0;
}
