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
int read01() {
	char ch = getchar();
	for(; ch != '.' && ch != '#'; ch = getchar());
	return ch == '#';
}
const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
int n, cr[MAXN], cc[MAXN], ans;
char a[MAXN][MAXN]; 
int main() {
	n = read();
	bool fl = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%s", a[i]+1);
		for(int j = 1; j <= n; j++) {
			if(a[i][j] == '#') {
				fl = 1;
				cr[i] ++;
				cc[j] ++;
			}
		}
	}
	if(!fl) {
		printf("-1\n");
		return 0;
	}
	int ans = n;
	for(int i = 1; i <= n; i++)
		if(cc[i]) ans = min(ans, n - cr[i]);
		else ans = min(ans, n - cr[i] + 1);
	for(int i = 1; i <= n; i++)
		if(cc[i] != n) ans ++;
	printf("%d\n", ans);
	return 0;
}
