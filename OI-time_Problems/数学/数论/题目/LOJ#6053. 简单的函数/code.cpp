#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
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
const ll MAXN = 1e10 + 5;
const int MAXK = 5e5 + 5, P = 1e9 + 7;
ll pls(ll a, ll b) {return a + b < P ? a + b : a + b - P;}
ll mns(ll a, ll b) {return a < b ? a + P - b : a - b;}
ll mul(ll a, ll b) {return a * b % P;}
ll n, sn, pr[MAXK], sp2[MAXK], sp1[MAXK], w[MAXK], g1[MAXK], g2[MAXK];
int ip[MAXK], tot, num, id1[MAXK], id2[MAXK];
void pre_gao(int n) {
	ip[1] = 1; 
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			sp1[tot] = pls(sp1[tot-1], i);
			sp2[tot] = pls(sp2[tot-1], 1);
		}
		for(int j = 1; j <= tot && i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}
ll S(ll x, int k) {
	if(pr[k] >= x) return 0;
	int t = x <= sn ? id1[x] : id2[n / x];
	ll ret = mns(mns(g1[t], sp1[k]), mns(g2[t], sp2[k]));
	if(n >= 2 && k == 0) ret = pls(ret, 2);
	for(int j = k+1; j <= tot && pr[j] * pr[j] <= x; j++) {
		ll p = pr[j];
		for(int e = 1; p <= x; e++, p *= pr[j]) {
			ret = pls(ret, mul(pr[j] ^ e, pls(S(x / p, j), int(e != 1))));
		}
	}
	return ret;
}
int main() {
	n = read(); sn = sqrt(n) + 1;
	pre_gao(sn);
	for(ll i = 1, j; i <= n; i = j + 1) {
		ll t = n / i; j = n / t;
		w[++num] = t;
		ll tmp = t % P;
		g1[num] = mns(tmp * (tmp + 1) / 2 % P, 1);
		g2[num] = mns(tmp, 1);
		if(t <= sn) id1[t] = num;
		else id2[n / t] = num;
	}
	for(int j = 1; j <= tot; j++)
		for(int i = 1; i <= num && pr[j] * pr[j] <= w[i]; i++) {
			ll nxt = w[i] / pr[j];
			int t = nxt <= sn ? id1[nxt] : id2[n / nxt];
			g1[i] = mns(g1[i], mul(pr[j],  mns(g1[t], sp1[j-1])));
			g2[i] = mns(g2[i], mns(g2[t], sp2[j-1]));
		}
	printf("%lld\n", pls(1, S(n, 0)));

	return 0;
}
