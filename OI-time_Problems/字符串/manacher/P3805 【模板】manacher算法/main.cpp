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
const int MAXN = 3e7 + 5;
char s[MAXN];
int n, r[MAXN];
int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = n; i >= 1; i--) s[i * 2 + 1] = s[i], s[i * 2 + 2] = '#';
	s[1] = '@', s[2] = '#'; n = 2 * n + 2;
	
	for(int c = 0, i = 1; i <= n; i++) {
		if(i < c + r[c]) r[i] = min(c + r[c] - i, r[2 * c - i]);
		while(i + r[i] <= n && s[i + r[i]] == s[i - r[i]]) r[i]++;
		if(i + r[i] > c + r[c]) c = i;
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = max(ans, r[i] - 1);
	printf("%d\n", ans);
	return 0;
}
