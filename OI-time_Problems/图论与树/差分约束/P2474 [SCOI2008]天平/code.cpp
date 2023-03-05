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
char readc() {
	char ch = getchar();
	for(; ch != '+' && ch != '-' && ch != '?' && ch != '='; ch = getchar());
	return ch;
}
const int MAXN = 55;
int mx[MAXN][MAXN], mn[MAXN][MAXN];
int n, A, B;
int main() {
	n = read(); A = read(); B = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			char opt = readc();
			if(opt == '+') {//i>j
				mx[i][j] = 2; mn[i][j] = 1;
			} else if(opt == '-') {//i<j
				mx[i][j] = -1;
				mn[i][j] = -2;
			} else if(opt == '=') {
				mx[i][j] = mn[i][j] = 0;
			} else if(opt == '?') {
				mx[i][j] = 2; mn[i][j] = -2;
			}
		}
	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				mx[i][j] = min(mx[i][j], mx[i][k] + mx[k][j]),
				mn[i][j] = max(mn[i][j], mn[i][k] + mn[k][j]);
	int c1 = 0, c2 = 0, c3 = 0;
	for(int i = 1; i <= n; i++) if(i != A && i != B)
		for(int j = i+1; j <= n; j++) if(j != A && j != B) {
			if(mn[A][i] > mx[j][B] || mn[A][j] > mx[i][B]) c1++;
			if((mx[A][i] == mn[A][i] && mx[j][B] == mn[j][B] && mx[A][i] == mx[j][B]) || (mx[A][j] == mn[A][j] && mx[i][B] == mn[i][B] && mx[A][j] == mx[i][B])) c2++;
			if(mx[A][i] < mn[j][B] || mx[A][j] < mn[i][B]) c3++;
		}
	printf("%d %d %d\n", c1, c2, c3);
	return 0;
}
