#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 3e3 + 5;
constexpr int P = 1e9 + 7;
int MOD(int v) {return v >= P ? v - P : v;}
struct mint {
	int v;
	mint(int v = 0) : v(v) {}
};
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
int n, x[MAXN], lsh[MAXN], _lsh, cnt[MAXN];
void LSH() {
	sort(lsh + 1, lsh + 1 + _lsh);
	_lsh = unique(lsh + 1, lsh + 1 + _lsh) - lsh - 1;
}
int LSH(int x) {
	return lower_bound(lsh + 1, lsh + 1 + _lsh, x) - lsh;
}
mint f[MAXN][MAXN], F[MAXN][MAXN];
void work() {
	cin >> n;
	_lsh = 0;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		lsh[++_lsh] = x[i];
	}
	LSH();
	for (int i = 0; i <= _lsh; i++)
		cnt[i] = 0;
	for (int i = 1; i <= n; i++)
		cnt[LSH(x[i])]++;
	for (int i = 1; i <= _lsh; i++)
		cnt[i] += cnt[i-1];
	f[0][0] = F[0][0] = 1;
	for (int v = 1; v <= _lsh; v++)
		for (int k = 0; k <= cnt[v]; k++) {
			f[v][k] = F[v-1][min(k, cnt[v-1])];
			F[v][k] = (k == 0 ? 0 : F[v][k-1]) + f[v][k];
		}
	for (int k = 1; k <= n; k++)
		cout << f[_lsh][k].v << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}
