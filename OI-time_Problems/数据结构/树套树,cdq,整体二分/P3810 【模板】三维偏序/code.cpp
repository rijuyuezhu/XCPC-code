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
const int MAXN = 1e5 + 5;
const int MAXK = 2e5 + 5;
int n, K, tot, ans[MAXN], f[MAXN];
struct Item {int k, a, b, c;}q[MAXN * 2], tmp[MAXN * 2];
bool cmp1(const Item& A, const Item& B) {
	return A.a == B.a ? A.k < B.k : A.a < B.a;
}
bool cmp2(const Item& A, const Item& B) {
	return A.b == B.b ? A.k < B.k : A.b < B.b;
}
namespace BIT {
	int t[MAXK];
	void add(int i, int v) {for(; i <= K; i += i&-i) t[i] += v;}
	int sum(int i) {int ret = 0; for(; i; i -= i&-i) ret += t[i]; return ret;}
}
void CDQ(int l, int r) {
	if(l >= r) return;
	int m = (l + r) >> 1; CDQ(l, m); CDQ(m+1, r);
	int i = l, j = m+1, k = l;
	while(i <= m && j <= r) {
		if(cmp2(q[i], q[j])) {
			if(q[i].k == 0) BIT::add(q[i].c, 1);
			tmp[k++] = q[i++];
		} else {
			if(q[j].k) ans[q[j].k] += BIT::sum(q[j].c);
			tmp[k++] = q[j++];
		}
	}
	while(i <= m) {
		if(q[i].k == 0) BIT::add(q[i].c, 1);
		tmp[k++] = q[i++];
	}
	while(j <= r) {
		if(q[j].k) ans[q[j].k] += BIT::sum(q[j].c);
		tmp[k++] = q[j++];
	}
	for(int t = l; t <= m; t++) if(q[t].k == 0) BIT::add(q[t].c, -1);
	for(int t = l; t <= r; t++) q[t] = tmp[t];
}
int main() {
	n = read(); K = read();
	for(int i = 1; i <= n; i++) {
		int a = read(), b = read(), c = read();
		q[++tot] = (Item){0, a, b, c};
		q[++tot] = (Item){i, a, b, c};
	}
	sort(q + 1, q + 1 + tot, cmp1);
	CDQ(1, tot);
	for(int i = 1; i <= n; i++) f[ans[i]-1]++;
	for(int i = 0; i < n; i++) printf("%d\n", f[i]);
	return 0;
}
