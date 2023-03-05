#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
const int MAXN = 5e4 + 5;
int n, bel[MAXN], B, num, L[MAXN], R[MAXN];
ll a[MAXN], tag[MAXN];
vector<int> bod[MAXN], t1, t2;
bool cmp(int x, int y) {return a[x] < a[y];}
void init() {
	B = sqrt(n * log(n) / log(2)) + 1;
	for(int i = 1; i <= n; i++) bel[i] = (i - 1) / B + 1, bod[bel[i]].push_back(i);
	num = (n - 1) / B + 1;
	for(int i = 1; i <= num; i++) {
		L[i] = (i-1) * B + 1, R[i] = min(n, i * B);
		sort(bod[i].begin(), bod[i].end(), cmp);
	}
}
void refix(int l, int r, ll c) {
	int k = bel[l];
	t1.clear(); t2.clear();
	for(int i = 0; i < bod[k].size(); i++)
		if(l <= bod[k][i] && bod[k][i] <= r)
			a[bod[k][i]] += c, t1.push_back(bod[k][i]);
		else t2.push_back(bod[k][i]);
	bod[k].clear();
	for(int i = 0, j = 0; i < t1.size() || j < t2.size();) {
		if(j >= t2.size() || (i < t1.size() && cmp(t1[i], t2[j])))
			bod[k].push_back(t1[i++]);
		else bod[k].push_back(t2[j++]);
	}
}
void add(int l, int r, ll c) {
	if(bel[l] == bel[r]) {
		refix(l, r, c);
		return ;
	}
	refix(l, R[bel[l]], c);
	refix(L[bel[r]], r, c);
	for(int i = bel[l]+1; i <= bel[r]-1; i++) tag[i] += c;
}
int qrybf(int l, int r, ll v) {
	int ans = 0;
	v -= tag[bel[l]];
	for(int i = l; i <= r; i++)
		if(a[i] < v) ans++;
	return ans;
}
int qrywh(int k, ll v) {
	v -= tag[k];
	int l = 0, r = bod[k].size() - 1, ans = 0;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(a[bod[k][m]] < v) ans += m - l + 1, l = m + 1;
		else r = m-1;
	}
	return ans;
}
int qry(int l, int r, ll v) {
	if(bel[l] == bel[r]) {
		return qrybf(l, r, v);
	}
	int ans = 0;
	ans += qrybf(l, R[bel[l]], v);
	ans += qrybf(L[bel[r]], r, v);
	for(int i = bel[l]+1; i <= bel[r]-1; i++)
		ans += qrywh(i, v);
	return ans;
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	init();
	for(int i = 1; i <= n; i++) {
		int opt = read(), l = read(), r = read(); ll c = read();
		if(opt == 0) add(l, r, c);
		else printf("%d\n", qry(l, r, c * c));
	}
	return 0;
}
