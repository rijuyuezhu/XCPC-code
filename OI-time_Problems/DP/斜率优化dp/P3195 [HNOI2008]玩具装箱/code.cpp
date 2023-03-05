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
const int MAXN = 5e4 + 5;
int n, hd, tl;
ll L, C[MAXN], S[MAXN], dp[MAXN], q[MAXN];
ll sqr(ll x) {return x*x;}
ll calc(int j, int i) {//the contribution of j when calc i
	return dp[j] + sqr(S[i] - S[j] - L);
}
ll Val(int i) {return dp[i] + sqr(S[i]) + 2 * L * S[i];}
bool check(int i, int j, int k) {//k(i,j)>=k(j,k) ? (i<j<k)
	return (Val(j) - Val(i)) * (S[k] - S[j]) >= (Val(k) - Val(j)) * (S[j] - S[i]);
}
int main() {
	n = read(); L = read();
	for(int i = 1; i <= n; i++) C[i] = read();
	L++;
	for(int i = 1; i <= n; i++) S[i] = S[i-1] + C[i] + 1;
	hd = tl = 1; q[1] = 0;
	for(int i = 1; i <= n; i++) {
		while(hd < tl && calc(q[hd], i) >= calc(q[hd+1], i)) hd++;
		dp[i] = calc(q[hd], i);
		while(hd < tl && check(q[tl-1], q[tl], i)) tl--;
		q[++tl] = i;
	}
	printf("%lld\n", dp[n]);
	return 0;
}
