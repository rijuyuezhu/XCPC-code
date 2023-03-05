#include<cstdio>
#include<cstring>
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
const int BAS = 8e8;
const ll PRES = 1130;
const int N = 2e8, SQN = 4e4;
int mu[N+5], lst[N+5], pr[SQN+5], ip[SQN+5], tot;
void sieve(int n) {
	ip[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
		}
		for(int j = 1; j <= tot && pr[j] <= n / i; j++) {
			int k = i * pr[j];
			ip[k] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}
int main() {
	sieve(SQN);
	for(int i = 1; i <= N; i++)	mu[i] = 1, lst[i] = BAS + i;
	for(int j = 1; j <= tot; j++)
		for(int i = pr[j] * (BAS / pr[j] + 1); i <= BAS + N; i += pr[j]) {
			mu[i-BAS] *= -1; lst[i-BAS] /= pr[j];
			if(lst[i-BAS] % pr[j] == 0)
				mu[i-BAS] = 0;
		}
	for(int i = 1; i <= N; i++) if(lst[i] > 1) mu[i] *= -1;
	ll sum = PRES; int mx = -1, mn = -1; ll mxv = -1, mnv = -1;
	for(int i = 1; i <= N; i++) {
		sum += mu[i];
		if(mx == -1 || sum > mxv) mx = BAS+i, mxv = sum;
		if(mn == -1 || sum < mnv) mn = BAS+i, mnv = sum;
	}
	printf("mx = %d, mxv = %lld\nmn = %d, mnv = %lld\nsum=%lld\n", mx, mxv, mn, mnv, sum);
	return 0;
}
