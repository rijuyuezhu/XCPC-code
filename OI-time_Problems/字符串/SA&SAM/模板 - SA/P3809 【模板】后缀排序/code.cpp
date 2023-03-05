#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e6 + 5;
char s[MAXN];
int n, sa[MAXN], rk[MAXN], x[MAXN], y[MAXN << 1], c[MAXN];
void SuffixSort() {
	int m = 'z';
	for(int i = 1; i <= n; i++) c[x[i] = s[i]]++;
	for(int i = 1; i <= m; i++) c[i] += c[i-1];
	for(int i = n; i >= 1; i--) sa[c[x[i]]--] = i;
	for(int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for(int i = n - k + 1; i <= n; i++) y[++num] = i;
		for(int i = 1; i <= n; i++) if(sa[i] > k) y[++num] = sa[i] - k;

		for(int i = 1; i <= m; i++) c[i] = 0;
		for(int i = 1; i <= n; i++) c[x[i]]++;
		for(int i = 2; i <= m; i++) c[i] += c[i-1];
		for(int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i], y[i] = 0;

		for(int i = 1; i <= n; i++) swap(x[i], y[i]);
		x[sa[1]] = 1; num = 1;
		for(int i = 2; i <= n; i++)
			x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i] + k] == y[sa[i-1] + k]) ? num : ++num;
		m = num;
		if(num == n) break;
	}
	for(int i = 1; i <= n; i++) rk[sa[i]] = i;
}


int main() {
	scanf("%s", s+1); n = strlen(s+1);
	SuffixSort();
	for(int i = 1; i <= n; i++) printf("%d ", sa[i]);
	printf("\n");
	return 0;
}
