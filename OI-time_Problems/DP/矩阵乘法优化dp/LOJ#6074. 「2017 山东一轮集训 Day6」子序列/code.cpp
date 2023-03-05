#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5, P = 1e9 + 7, M = 9;
namespace MINT {
	struct mint {
		int v;
		mint(int v = 0) : v(v) {}
	};
	int MOD(int v) {return v >= P ? v - P : v;}
	mint tran(int v) {return MOD(v % P + P);}
	mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
	mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
	mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}
	mint qpow(mint a, int n=P-2) {mint ret = 1; for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a; return ret;}
} using namespace MINT;
char s[MAXN];
int n, q;
mint f[MAXN][M+1], b[MAXN][M+1], tag[MAXN][M+1], matf[M+1][M+1], matb[M+1][M+1];
int main() {
	scanf("%s", s+1); n = strlen(s+1);
	q = read();
	for(int i = 0; i <= M; i++) f[0][i] = 1, matf[i][i] = 1, matb[i][i] = 1, tag[0][i] = 0;
	b[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		int c = s[i] - 'a' + 1;
		for(int j = 0; j <= M; j++) {
			f[i][j] = f[i-1][j] - matf[c][j] + f[i-1][j];
			matf[c][j] = f[i-1][j];
			tag[i][j] = tag[i-1][j] - (matb[j][c] + tag[i-1][j]); matb[j][c] = matb[j][c] + (matb[j][c] + tag[i-1][j]);
			b[i][j] = matb[j][0] + tag[i][j];
		}
	}
	for(int i = 1; i <= q; i++) {
		int l = read(), r = read();
		mint ans = 0;
		for(int j = 0; j <= M; j++) ans = ans + f[r][j] * b[l-1][j];
		printf("%d\n", (ans-1).v);
	}
	return 0;
}
