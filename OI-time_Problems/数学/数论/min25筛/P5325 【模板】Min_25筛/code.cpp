#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
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
const int P = 1e9 + 7, MAXK = 5e5+5, inv6 = 166666668, inv2 = 500000004;
const ll MAXN = 1e10+5;
ll n, sn, w[MAXK], pr[MAXK], sp1[MAXK], sp2[MAXK], g1[MAXK], g2[MAXK];
int ip[MAXK], tot, num, id1[MAXK], id2[MAXK];
void pre_gao(int n) {
	ip[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			sp1[tot] = (sp1[tot-1] + 1ll * i * i) % P;
			sp2[tot] = (sp2[tot-1] + i) % P;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}
ll S(ll x, int k) {
	if(pr[k] >= x) return 0;
	int t = x <= sn ? id1[x] : id2[n / x];
	ll ret = ((g1[t] - sp1[k] + P) - (g2[t] - sp2[k] + P) % P) % P;
	for(int j = k+1; j <= tot && pr[j] * pr[j] <= x; j++) {
		ll p = pr[j];
		for(int e = 1; p <= x; e++, p *= pr[j]) {
			ll tmp = p % P;
			ret = (ret + tmp * (tmp - 1) % P * (S(x / p, j) + int(e != 1))) % P;
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
		g1[num] = (tmp * (tmp + 1) % P * (tmp + tmp + 1) % P * inv6 + P - 1) % P;
		g2[num] = (tmp * (tmp + 1) % P * inv2 + P - 1) % P;
		//the initial value of g(-,0)
		if(t <= sn) id1[t] = num;
		else id2[n / t] = num;
	}
	
	//calc from g(-,j-1) to g(-,j)
	for(int j = 1; j <= tot; j++) 
		for(int i = 1; i <= num && pr[j] * pr[j] <= w[i]; i++) {
			ll nxt = w[i] / pr[j]; int t = nxt <= sn ? id1[nxt] : id2[n / nxt];
			g1[i] = (g1[i] - pr[j] * pr[j] % P * (g1[t] - sp1[j-1]) % P + P) % P;
			g2[i] = (g2[i] - pr[j] * (g2[t] - sp2[j-1]) % P + P) % P;
		}
	printf("%lld\n", (S(n, 0) + 1));
	return 0;
}
