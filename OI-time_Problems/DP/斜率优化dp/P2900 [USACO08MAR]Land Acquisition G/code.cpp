#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef long double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 5e4 + 5;
int n, q[MAXN], hd, tl;
ll f[MAXN];
struct Node {ll w, l;}t[MAXN];
bool operator < (const Node& a, const Node& b) {
	return a.l == b.l ? a.w > b.w : a.l > b.l;
}
db slope(int i, int j) {
	return db(f[i] - f[j]) / (t[i+1].l - t[j+1].l);
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) t[i].w = read(), t[i].l = read();
	sort(t + 1, t + 1 + n);
	int tot = 1;
	for(int i = 2; i <= n; i++) 
		if(t[tot].w < t[i].w) t[++tot] = t[i];
	n = tot;
	q[hd = tl = 1] = 0;
	for(int i = 1; i <= n; i++) {
		while(hd < tl && slope(q[hd], q[hd+1]) >= -t[i].w) hd++;
		f[i] = f[q[hd]] + t[i].w * t[q[hd]+1].l;
		while(hd < tl && slope(q[tl-1], q[tl]) <= slope(q[tl], i)) tl--;
		q[++tl] = i;
	}
	printf("%lld\n", f[n]);
		
	return 0;
}
