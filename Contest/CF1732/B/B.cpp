#include <cstdio>
const int MAXN = 1e5 + 5;
int n;
char s[MAXN];
int f[MAXN][2], g[MAXN][2];
void work() {
	scanf("%d", &n);
	scanf("%s", s+1);
	f[n][0] = s[n] == '0' ? 0 : 1;
	f[n][1] = s[n] == '1' ? 0 : 1;
	g[1][0] = s[1] == '0' ? 0 : 1;
	g[1][1] = s[1] == '1' ? 1 : 0;
	for(int i = n-1; i >= 1; i--)
		if(s[i] == '1') {
			f[i][0] = 1 + f[i+1][1];
			f[i][1] = f[i+1][1];
		} else {
			f[i][0] = f[i+1][0];
			f[i][1] = 1 + f[i+1][1];
		}
	for(int i = 2; i <= n; i++) 
		if(s[i] == '1') {
			g[i][0] = 1 + g[i-1][1];
			g[i][1] = g[i-1][1];
		} else {
			g[i][0] = g[i-1][0];
			g[i][1] = 1 + g[i-1][0];
		}
}
int main() {
	int t;
	scanf("%d", &t);
	for(int i = 1; i <= t; i++)
		work();
	return 0;
}	
