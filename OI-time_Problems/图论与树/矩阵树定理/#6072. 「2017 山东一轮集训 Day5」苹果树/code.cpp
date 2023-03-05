#include<cstring>
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
const int MAXN = 45, P = 1e9 + 7;
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
	mint operator ++ (mint& a) {return a = a + 1;}
	mint operator -- (mint& a) {return a = a - 1;}
} using namespace MINT;
int n, m, lim, c[MAXN], a[MAXN];
vector<int> pres[MAXN], sufs[MAXN];
mint h[MAXN];
void calch() {
	for(int s = 0; s < (1 << (m/2)); s++) {
		int cnt = 0, sum = 0;
		for(int i = 0; i < m/2; i++)
			if((s >> i) & 1) {
				cnt++; sum += a[i+1];
			}
		pres[cnt].push_back(sum);
	}
	for(int s = 0; s < (1 << (m-m/2)); s++) {
		int cnt = 0, sum = 0;
		for(int i = 0; i < m-m/2; i++)
			if((s >> i) & 1) {
				cnt++; sum += a[i+1+m/2];
			}
		sufs[cnt].push_back(sum);
	}
	for(int i = 0; i <= m/2; i++) {
		if(pres[i].empty()) continue;
		sort(pres[i].begin(), pres[i].end());
		for(int j = 0; j <= m-m/2; j++) {
			if(sufs[j].empty()) continue;
			sort(sufs[j].begin(), sufs[j].end());
			vector<int> &A = pres[i], &B = sufs[j];
			int q = B.size()-1; mint ans = 0;
			for(int p = 0; p < (int)A.size() && q >= 0; p++) {
				while(q >= 0 && A[p] + B[q] > lim) q--;
				if(q < 0) break;
				ans += q+1;
			}
			h[i+j] += ans;
		}
	}
}
mint C[MAXN][MAXN], f[MAXN], g[MAXN];
mint e[MAXN][MAXN];
void addedge(int u, int v) {--u, --v; ++e[u][u]; ++e[v][v]; --e[u][v]; --e[v][u];}//delete the line 1.
mint det(mint a[][MAXN], int n) {
	int f = 0;
	for(int i = 1; i <= n; i++) {
		int num = -1;
		for(int j = i; j <= n; j++)
			if(a[j][i].v) { num = j; break; }
		if(num == -1) return 0;
		if(i != num) {
			f ^= 1;
			for(int j = i; j <= n; j++) swap(a[i][j], a[num][j]);
		}
		mint in = qpow(a[i][i]);
		for(int j = i+1; j <= n; j++) {
			mint t = in * a[j][i];
			for(int k = i; k <= n; k++) a[j][k] -= a[i][k] * t;
		}
	}
	mint ans = 1; for(int i = 1; i <= n; i++) ans *= a[i][i];
	if(f) ans = 0-ans;
	return ans;
}
mint calcg(int k) {
	for(int i = 1; i <= n-1; i++)
		for(int j = 1; j <= n-1; j++)
			e[i][j] = 0;
	for(int i = 1; i <= k; i++) {
		for(int j = i+1; j <= k; j++) addedge(i, j);
		for(int j = m+1; j <= n; j++) addedge(i, j);
	}
	for(int i = k+1; i <= m; i++)
		for(int j = m+1; j <= n; j++)
			addedge(i, j);
	for(int i = m+1; i <= n; i++)
		for(int j = i+1; j <= n; j++) 
			addedge(i, j);
	return det(e, n-1);
}
int main() {
	n = read(), lim = read();
	for(int i = 1; i <= n; i++) {
		c[i] = read();
		if(c[i] != -1) a[++m] = c[i];
	}
	calch();
	for(int i = 0; i <= m; i++) g[i] = calcg(i);
	C[0][0] = 1;
	for(int i = 1; i <= m; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
	for(int i = 0; i <= m; i++) {
		f[i] = 0;
		for(int j = 0; j <= i; j++)
			if((i - j) & 1) f[i] -= C[i][j] * g[j];
			else f[i] += C[i][j] * g[j];
	}
	mint ans = 0;
	for(int i = 0; i <= m; i++) ans += h[i] * f[i];
	printf("%d\n", ans.v);
	return 0;
}
