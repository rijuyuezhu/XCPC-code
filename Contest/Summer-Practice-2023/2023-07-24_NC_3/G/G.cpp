#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
constexpr int P = 980000023;
constexpr int MAXN = 2005;
int MOD(int v) { return v >= P ? v - P : v; }
struct mint {
	int v;
	mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return MOD(1ll * a.v * b.v % P);}
const mint A = 253, B = 856;
mint S[MAXN][MAXN];
int n, m, ch[MAXN][MAXN], re[MAXN][MAXN];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cin >> ch[i][j];
			re[n-i+1][m-j+1]
		}
	return 0;
}
