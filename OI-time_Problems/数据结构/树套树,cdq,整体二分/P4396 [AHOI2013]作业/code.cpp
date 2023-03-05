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
struct Item {int a, b, c, k, w;}q[MAXN * 5], tmp[MAXN * 5];
int tot, n, m, lst[MAXN], ans1[MAXN], ans2[MAXN];
bool cmp1(const Item& x, const Item& y) {return x.a == y.a ? x.k < y.k : x.a < y.a;}
bool cmp2(const Item& x, const Item& y) {return x.b == y.b ? x.k < y.k : x.b < y.b;}
namespace BIT {
	int t[MAXN];
	void add(int i, int v) {for(i++; i <= n+1; i += i & -i) t[i] += v;}
	int sum(int i) {int ret = 0; for(i++; i; i -= i & -i) ret += t[i]; return ret;}
}
void CDQ(int l, int r) {
	if(l >= r) return;
	int m = (l + r) >> 1; CDQ(l, m); CDQ(m+1, r);
	int i = l, j = m+1, k = l, cnt = 0;
	while(i <= m && j <= r) {
		if(cmp2(q[i], q[j])) {
			if(q[i].k == 0) BIT::add(q[i].c, 1), cnt++;
			tmp[k++] = q[i++];
		} else {
			if(q[j].k) {
				ans1[q[j].k] += q[j].w * cnt;
				ans2[q[j].k] += q[j].w * BIT::sum(q[j].c);
			}
			tmp[k++] = q[j++];
		}
	}
	while(i <= m) {
		if(q[i].k == 0) BIT::add(q[i].c, 1), cnt++;
		tmp[k++] = q[i++];
	}
	while(j <= r) {
		if(q[j].k) {
			ans1[q[j].k] += q[j].w * cnt;
			ans2[q[j].k] += q[j].w * BIT::sum(q[j].c);
		}
		tmp[k++] = q[j++];
	}
	for(int t = l; t <= m; t++) if(q[t].k == 0) BIT::add(q[t].c, -1);
	for(int t = l; t <= r; t++) q[t] = tmp[t];
}
	

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		int b = read(), c = lst[b];
		lst[b] = i;
		q[++tot] = (Item){i, b, c, 0, 0};
	}
	for(int i = 1; i <= m; i++) {
		int l = read(), r = read(), a = read(), b = read();
		q[++tot] = (Item){r, b, l-1, i, 1};
		q[++tot] = (Item){l-1, b, l-1, i, -1};
		q[++tot] = (Item){r, a-1, l-1, i, -1};
		q[++tot] = (Item){l-1, a-1, l-1, i, 1};
	}
	sort(q + 1, q + 1 + tot, cmp1);
	CDQ(1, tot);
	for(int i = 1; i <= m; i++) printf("%d %d\n", ans1[i], ans2[i]);
	return 0;
}
