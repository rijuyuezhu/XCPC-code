#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
const int MAXN = 1e5 + 5, P = 1000000087;

int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
	int v;
	mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
bool operator < (mint a, mint b) {return a.v < b.v;}
bool operator == (mint a, mint b) {return a.v == b.v;}
struct Hs {
	mint x, y;
	Hs(mint x = 0, mint y = 0) :x(x), y(y) {}
};
Hs operator + (Hs a, Hs b) {return Hs(a.x + b.x, a.y + b.y);}
Hs operator - (Hs a, Hs b) {return Hs(a.x - b.x, a.y - b.y);}
Hs operator * (Hs a, Hs b) {return Hs(a.x * b.x, a.y * b.y);}
bool operator < (Hs a, Hs b) {return a.x == b.x ? a.y < b.y : a.x < b.x;}
bool operator == (Hs a, Hs b) {return a.x == b.x && a.y == b.y;}
const Hs Bas = Hs(251, 3137);
int n, K;
vector<int> G[MAXN], kson[MAXN];
vector<Hs> buk;
int eul[MAXN * 2], _eul, st[MAXN], ed[MAXN], dep[MAXN], seq[MAXN];
Hs Bpow[MAXN * 2], hs[MAXN * 2];
void dfs(int u, int f) {
	dep[u] = dep[f] + 1; st[u] = _eul+1;
	for(int i = 0; i < (int)G[u].size(); i++) {
		int v = G[u][i];
		eul[++_eul] = 1;
		dfs(v, u);
		eul[++_eul] = 0;
	}
	ed[u] = _eul;
}
void gao(int u) {
	seq[dep[u]] = u;
	if(dep[u] > K) kson[seq[dep[u]-K]].push_back(u);
	for(int i = 0; i < (int)G[u].size(); i++) {
		int v = G[u][i];
		gao(v);
	}
}
bool check() {
	for(int i = 1; i <= n; i++) kson[i].clear();
	gao(1);
	buk.clear();
	for(int u = 1; u <= n; u++) {
		if(kson[u].size() == 0) continue;
		Hs ret = Hs(0, 0);
		int s = st[u], t;
		for(int i = 0; i < (int)kson[u].size(); i++) {
			int v = kson[u][i];
			t = st[v] - 1;
			ret = ret * Bpow[t-s+1] + hs[t] - hs[s-1] * Bpow[t-s+1];
			s = ed[v] + 1;
		}
		t = ed[u];
		ret = ret * Bpow[t-s+1] + hs[t] - hs[s-1] * Bpow[t-s+1];
		buk.push_back(ret);
	}
	sort(buk.begin(), buk.end());
	for(int i = 1; i < (int)buk.size(); i++)
		if(buk[i] == buk[i-1]) return 1;
	return 0;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		int x = read();
		for(int j = 1; j <= x; j++) G[i].push_back(read());
	}
	dfs(1, 0);
	Bpow[0] = Hs(1, 1);
	for(int i = 1; i <= _eul; i++) {
		Bpow[i] = Bpow[i-1] * Bas;
		hs[i] = hs[i-1] * Bas + Hs(eul[i], eul[i]);
	}
	int l = 0, r = n, ans = -1;
	while(l <= r) {
		K = (l + r) >> 1;
		if(check()) ans = K, l = K + 1;
		else r = K - 1;
	}
	printf("%d\n", ans);
	return 0;
}
