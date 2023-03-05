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
const int P = 1e9 + 7;
const int MAXN = 1e6 + 5;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a - b + P : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
char s[MAXN];
int n, nxt[MAXN], dep[MAXN], ans;

void work() {
	scanf("%s", s + 1); n = strlen(s + 1);
	nxt[1] = 0; dep[1] = 1;
	for(int i = 2, j = 0; i <= n; i++) {
		while(j && s[j+1] != s[i]) j = nxt[j];
		if(s[j+1] == s[i]) j++;
		nxt[i] = j; dep[i] = dep[j] + 1;
	}
	ans = 1;
	for(int i = 1, j = 0; i <= n; i++) {
		while(j && s[j+1] != s[i]) j = nxt[j];
		if(s[j+1] == s[i]) j++;
		while(j*2 > i) j = nxt[j];
		ans = mul(ans, dep[j]+1);
	}
	printf("%d\n", ans);

}
int main() {
	int n = read();
	while(n--) work();
	return 0;
}
