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
const int MAXN = 2e5 + 5;

int n, w, a[MAXN], b[MAXN], ans;
int nxt[MAXN];
int main() {
	n = read(), w = read();
	if(w == 1) {
		printf("%d\n", n);
		return 0;
	}
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= w; i++) b[i] = read();
	for(int i = 1; i < n; i++) a[i] -= a[i+1];
	for(int i = 1; i < w; i++) b[i] -= b[i+1];
	nxt[1] = 0; int j = 0;
	for(int i = 2; i < w; i++) {
		while(j && b[j+1] != b[i]) j = nxt[j];
		if(b[j+1] == b[i]) j++;
		nxt[i] = j;
	}
	j = 0;
	for(int i = 1; i < n; i++) {
		while(j && b[j+1] != a[i]) j = nxt[j];
		if(b[j+1] == a[i]) j++;
		if(j == w - 1) {ans++; j = nxt[j];}
	}
	printf("%d\n", ans);
	return 0;
}
