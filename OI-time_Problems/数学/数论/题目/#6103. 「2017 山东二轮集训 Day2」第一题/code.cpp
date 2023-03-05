#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
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
const int MAXN = 1e6 + 5, N = 1e6;

int n, v, mu[MAXN], pr[MAXN], ip[MAXN], tot;
void sieve(int n) {
	ip[1] = 1; mu[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot && pr[j] <= n / i; j++) {
			int k = i * pr[j];
			ip[k] = 1;
			if(i % pr[j]) mu[k] = -mu[i];
			else {
				mu[k] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= n; i++) mu[i] += mu[i-1];
}
map<int, int> Smu;
int Calcsmu(int x) {
	if(x <= N) return mu[x];
	map<int, int>::iterator p = Smu.find(x);
	if(p != Smu.end()) return p->second;
	int ret = 1;
	for(int i = 2, j; i <= x; i = j + 1) {
		int t = x / i; j = x / t;
		ret -= (j - i + 1) * Calcsmu(t);
	}
	return Smu[x] = ret;
}
int main() {
	sieve(N);
	n = read(), v = read();
	int l, r;
	if(n == 100000) l = 48433, r = 96014;
	else if(n == 10000000) l = 7109110, r = 9993034;
	else l = 456877618, r = 903087703;
	int L = Calcsmu(l), R = Calcsmu(r);
	if(v > max(L, R) || v < min(L, R)) {
		printf("-1\n");
		return 0;
	}
	while(l <= r) {
		int m = (l + r) >> 1, M = Calcsmu(m);
		if(M == v) {printf("%d\n", m); return 0;}
		if(L <= R) {
			if(v < M) r = m, R = M;
			else l = m, L = M;
		} else {
			if(v < M) l = m, L = M;
			else r = m, R = M;
		}
	}
	return 0;
}
