#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
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
const int MAXN = 1e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, num, B, L[MAXN], R[MAXN], bel[MAXN], tag[MAXN];
ll a[MAXN];
vector<int> bod[MAXN], t1, t2;
bool cmp(int x, int y) {return a[x] < a[y];}
void init() {
	B = sqrt(n * log(n) / log(2));
	for(int i = 1; i <= n; i++) {
		bel[i] = (i-1) / B + 1;
		bod[bel[i]].push_back(i);
	}
	num = (n-1) / B + 1;
	for(int i = 1; i <= num; i++) {
		L[i] = (i-1) * B + 1, R[i] = i * B;
		sort(bod[i].begin(), bod[i].end(), cmp);
	}
}
void addwh(int k, ll v) {tag[k] += v;}
void addbf(int l, int r, ll v) {
	t1.clear(); t2.clear();
	int k = bel[l];
	for(int i = 0; i < bod[k].size(); i++)
		if(l <= bod[k][i] && bod[k][i] <= r)
			a[bod[k][i]] += v, t1.push_back(bod[k][i]);
		else t2.push_back(bod[k][i]);
	bod[k].clear();
	for(int i = 0, j = 0; i < t1.size() || j < t2.size(); ) {
		if(j >= t2.size() || (i < t1.size() && cmp(t1[i], t2[j])))
			bod[k].push_back(t1[i++]);
		else bod[k].push_back(t2[j++]);
	}
}
void add(int l, int r, ll v) {
	if(bel[l] == bel[r]) {
		addbf(l, r, v);
		return;
	}
	addbf(l, R[bel[l]], v); addbf(L[bel[r]], r, v);
	for(int i = bel[l] + 1; i <= bel[r] - 1; i++) 
		addwh(i, v);
}
ll qrywh(int k, ll v) {
	int l = 0, r = bod[k].size()-1; ll ans = -INF;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(a[bod[k][m]] + tag[k] < v) {ans = a[bod[k][m]] + tag[k]; l = m+1;}
		else r = m-1;
	}
	return ans;
}

ll qrybf(int l, int r, ll v) {
	int k = bel[l];
	ll ans = -INF;
	for(int i = l; i <= r; i++)
		if(a[i] + tag[k] < v) ans = max(ans, a[i] + tag[k]);
	return ans;
}

ll qry(int l, int r, ll v) {
	ll ans = -INF;
	if(bel[l] == bel[r]) {
		ans = max(ans, qrybf(l, r, v));
	} else {
		ans = max(ans, qrybf(l, R[bel[l]], v));
		ans = max(ans, qrybf(L[bel[r]], r, v));
		for(int i = bel[l] + 1; i <= bel[r] - 1; i++) ans = max(ans, qrywh(i, v));
	}
	return ans == -INF ? -1 : ans;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	init();
	for(int i = 1; i <= n; i++) {
		int opt = read(), l = read(), r = read(); ll c = read();
		if(opt == 0) add(l, r, c);
		else printf("%lld\n", qry(l, r, c));
	}
	return 0;
}
