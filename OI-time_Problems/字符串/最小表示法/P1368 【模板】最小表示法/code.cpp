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
const int MAXN = 6e5 + 5;
int n, a[MAXN];
int Min_Show() {
	int t = 1, i = 2;
	while(i <= n) {
		int k = 0, tmp;
		while(a[t + k] == a[i + k]) k++;
		if(a[t + k] > a[i + k])
			tmp = i, i = max(i + 1, t + k + 1), t = tmp;
		else i += k+1;
	}
	return t;
}
			
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = a[i+n] = read();
	int ans = Min_Show();
	for(int i = ans; i <= ans + n - 1; i++) printf("%d ", a[i]);
	return 0;
}
