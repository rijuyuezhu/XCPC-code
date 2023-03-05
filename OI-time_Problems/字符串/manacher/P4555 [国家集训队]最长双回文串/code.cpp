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
const int MAXL = 2e5 + 5;
char s[MAXL];
int n, r[MAXL], lv[MAXL], rv[MAXL];
int main() {
	scanf("%s", s+1); n = strlen(s + 1);
	for(int i = n; i >= 1; i--) s[i * 2 + 1] = s[i], s[i * 2 + 2] = '#';
	s[1] = '@', s[2] = '#';
	n = 2 * n + 2;
	for(int c = 0, i = 1; i <= n; i++) {
		if(i < c + r[c]) r[i] = min(c + r[c] - i, r[2 * c - i]);
		while(i + r[i] <= n && s[i + r[i]] == s[i - r[i]]) r[i]++;
		if(i + r[i] > c + r[c]) c = i;
		lv[i + r[i] - 1] = max(lv[i + r[i] - 1], r[i] - 1);
		rv[i - r[i] + 1] = max(rv[i - r[i] + 1], r[i] - 1);
	}
	for(int i = 4; i <= n; i += 2) rv[i] = max(rv[i], rv[i - 2] - 2);
	for(int i = n - 2; i >= 2; i -= 2) lv[i] = max(lv[i], lv[i + 2] - 2);
	int ans = 0;
	for(int i = 2; i <= n; i += 2) if(lv[i] && rv[i]) ans = max(ans, lv[i] + rv[i]);
	printf("%d\n", ans);
	return 0;
}
