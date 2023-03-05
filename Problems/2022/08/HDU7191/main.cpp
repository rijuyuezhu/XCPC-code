/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-02 14:42:15
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1048&pid=1007
 * @Tag: 多项式，图论，生成函数
*/
#include<cstring>
#include<vector>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXN = 5e5 + 5;
const int P = 998244353;
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
namespace Poly {
   const int MAXL = (1 << 19) + 5, Bas = 1 << 19;
	typedef vector<mint> poly;
	mint inv[MAXL], fac[MAXL], ifac[MAXL], _g[MAXL];
	int tr[MAXL];
	void init() {
		inv[1] = 1; for(int i = 2; i < MAXL; i++) inv[i] = (P - P / i) * inv[P % i];
		fac[0] = ifac[0] = 1;
		for(int i = 1; i < MAXL; i++) fac[i] = fac[i-1] * i, ifac[i] = ifac[i-1] * inv[i];
		_g[0] = 1; _g[1] = qpow(3, (P-1) / Bas);
		for(int i = 2; i < Bas; i++) _g[i] = _g[i-1] * _g[1];
	}
	int glim(int n) {
		int lim = 1; for(; lim < n; lim <<= 1);
		return lim;
	}
	void DFT(poly& f, int lim) {
		if((int)f.size() < lim) f.resize(lim);
		for(int i = 0; i < lim; i++) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
		for(int i = 0; i < lim; i++) if(i < tr[i]) swap(f[i], f[tr[i]]);
		for(int l = 2, k = 1; l <= lim; l <<= 1, k <<= 1) 
			for(int i = 0; i < lim; i += l)
				for(int j = i; j < i+k; j++) {
					mint tt = f[j+k] * _g[Bas / l * (j-i)];
					f[j+k] = f[j] - tt;
					f[j] = f[j] + tt;
				}
	}
	void IDFT(poly& f, int lim) {
		DFT(f, lim); reverse(f.begin()+1, f.begin()+lim);
		for(int i = 1; i < lim; i++) f[i] *= inv[lim];
	}
   poly Mul(poly f, poly g) {
      int n = f.size() + g.size() - 1, lim = glim(n);
      DFT(f, lim), DFT(g, lim);
      for(int i = 0; i < lim; i++) f[i] *= g[i];
      IDFT(f, lim); f.resize(n); return f;
   }
} using namespace Poly;
typedef pair<int, int> pr;
int upto[MAXN], dist[MAXN], n, k, p[MAXN], cnt[MAXN], _cnt;
poly F[MAXN], f, g;
int getup(int x) {
   if(upto[x] == x) return x;
   int f = getup(upto[x]);
   dist[x] += dist[upto[x]];
   return upto[x] = f;
}
mint C(int n, int m) {
   if(n < 0 || m < 0 || n < m) return 0;
   return fac[n] * ifac[m] * ifac[n-m];
}
void work() {
   n = read(), k = read();
   _cnt = 0;
   for(int i = 1; i <= n; i++) p[i] = read(), upto[i] = i, dist[i] = 0;
   for(int i = 1; i <= n; i++) {
      int fx = getup(i), fy = getup(p[i]);
      if(fx == fy) {
         cnt[++_cnt] = dist[i] + dist[p[i]] + 1;
         continue;
      }
      upto[fx] = fy;
      dist[fx] = dist[p[i]] + 1;
   }
   priority_queue<pr, vector<pr>, greater<pr> > pq;
   for(int i = 1; i <= _cnt; i++) {
      int n = cnt[i];
      F[i].resize(n+1);
      for(int j = 0; j <= n; j++)
         F[i][j] = C(n-j, j) + C(n-j-1,j-1);
      pq.push(pr(F[i].size(), i));
   }
   while(pq.size() >= 2) {
      int i = pq.top().second; pq.pop();
      int j = pq.top().second; pq.pop();
      F[i] = Mul(F[i], F[j]); 
      pq.push(pr(F[i].size(), i));
   }
   int t = pq.top().second;
   printf("%d\n", F[t][k].v);
}
int main() {
   init();
   int T = read();
   while(T--) work();
   return 0;
}