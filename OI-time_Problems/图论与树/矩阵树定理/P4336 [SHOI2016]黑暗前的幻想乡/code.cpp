#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
typedef pair<int, int> pr;
#define fi first
#define se second
const int MAXN = 18, P = 1e9 + 7;
namespace MINT {
	struct mint {
		int v;
		mint(int v = 0) : v(v) {}
	};
	int MOD(int v) {return v >= P ? v - P : v;}
	mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
	mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
	mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
	mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
	mint operator += (mint& a, mint b) {return a = a + b;}
	mint operator -= (mint& a, mint b) {return a = a - b;}
	mint operator *= (mint& a, mint b) {return a = a * b;}
} using namespace MINT;
int n, U;
vector<pr> G[MAXN];
mint ans, a[MAXN][MAXN];
int Siz(int s) {
	int cnt = 0;
	while(s) {
		cnt += s & 1; s >>= 1;
	}
	return cnt;
}

mint det(mint a[][MAXN], int n) {
	int f = 0;
	for(int i = 1; i <= n; i++) {
		int num = -1;
		for(int j = i; j <= n; j++)
			if(a[i][j].v) {
				num = j;
				break;
			}
		if(num == -1) return 0;
		if(num != i) {
			f ^= 1;
			for(int j = i; j <= n; j++) swap(a[i][j], a[num][j]);
		}
		mint in = qpow(a[i][i]);
		for(int j = i+1; j <= n; j++) {
			mint t = a[j][i] * in;
			for(int k = i; k <= n; k++)
				a[j][k] -= a[i][k] * t;
		}
	}
	mint ans = 1;
	for(int i = 1; i <= n; i++) ans *= a[i][i];
	if(f) ans = 0-ans;
	return ans;
}
mint calc(int s) {
	for(int i = 1; i <= n-1; i++) for(int j = 1; j <= n-1; j++) a[i][j] = 0;
	for(int v = 0; v < n-1; v++) if((s >> v) & 1) {
		for(int i = 0; i < (int)G[v].size(); i++) {
			int x = G[v][i].fi - 1, y = G[v][i].se - 1;
			a[x][x] += 1; a[y][y] += 1;
			a[x][y] -= 1; a[y][x] -= 1;
		}
	}
	return det(a, n-1);
}
int main() {
	n = read(); U = (1 << (n-1)) - 1;
	for(int i = 0; i < n-1; i++) {
		int k = read();
		for(int j = 1; j <= k; j++) {
			int u = read(), v = read();
			G[i].push_back(pr(u, v));
		}
	}
	for(int s = 0; s <= U; s++)
		if((n-1-Siz(s)) & 1) ans -= calc(s);
		else ans += calc(s);
	printf("%d\n", ans.v);
	return 0;
}
