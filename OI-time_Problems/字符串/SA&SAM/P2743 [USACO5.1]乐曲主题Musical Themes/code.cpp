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
const int MAXN = 10005;
int n, s[MAXN], sa[MAXN], rk[MAXN], ht[MAXN], x[MAXN], y[MAXN], c[MAXN];
void SuffixSort() {
	int m = 305;
	for(int i = 1; i <= n; i++) c[x[i] = s[i]]++;
	for(int i = 2; i <= m; i++) c[i] += c[i-1];
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
		x[sa[1]] = num = 1;
		for(int i = 2; i <= n; i++)
			x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i] + k] == y[sa[i-1] + k]) ? num : ++num;
		if(num == n) break;
		m = num;
	}
}
void GetHeight() {
	for(int i = 1; i <= n; i++) rk[sa[i]] = i;
	for(int i = 1, k = 0; i <= n; i++) {
		if(k) k--;
		if(rk[i] == 1) {ht[rk[i]] = 0; continue;}
		int j = sa[rk[i]-1];
		while(i+k <= n && j+k <= n && s[i+k] == s[j+k]) k++;
		ht[rk[i]] = k;
	}
}
bool check(int k) {
	int mx = sa[1], mn = sa[1];
	for(int i = 2; i <= n; i++) {
		if(ht[i] >= k) {
			mx = max(mx, sa[i]); mn = min(mn, sa[i]);
			if(mx - mn > k) return 1;
		} else mx = mn = sa[i];
	}
	return 0;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) s[i] = read();
	n--;
	for(int i = 1; i <= n; i++) s[i] = s[i+1] - s[i] + 90;
	SuffixSort();
	GetHeight();
	int ans = -1, l = 0, r = n;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(check(m)) {ans = m; l = m+1;}
		else r = m-1;
	}
	ans++;
	if(ans <= 4) printf("0\n");
	else printf("%d\n", ans);
	return 0;
}
