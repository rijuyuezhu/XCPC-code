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
const int MAXL = 1e6 + 5;
int n, tot, m, len;
char ans[MAXL], tmp[MAXL];
int nxt[MAXL];
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		scanf("%s", tmp + 1); len = m = strlen(tmp + 1);
		tmp[++m] = '#';
		for(int i = max(1, tot - m + 1); i <= tot; i++) tmp[++m] = ans[i];
		nxt[1] = 0;
		for(int i = 2, j = 0; i <= m; i++) {
			while(j && tmp[j+1] != tmp[i]) j = nxt[j];
			if(tmp[j+1] == tmp[i]) j++;
			nxt[i] = j;
		}
		for(int i = nxt[m] + 1; i <= len; i++) ans[++tot] = tmp[i];
	}
	for(int i = 1; i <= tot; i++) putchar(ans[i]);
	printf("\n");
	return 0;
}
