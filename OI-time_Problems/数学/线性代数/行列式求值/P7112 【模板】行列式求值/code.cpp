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
#define ing ll
const int MAXN = 605;
int n, P, a[MAXN][MAXN];
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}

int calc() {
	int ans = 1, f = 0;
	for(int i = 1; i <= n; i++) {
		int num = i;
		for(int j = i+1; j <= n; j++)
			if(a[j][i] > a[num][i]) num = j;
		if(a[num][i] == 0) return 0;
		if(num != i) {
			for(int k = i; k <= n; k++) swap(a[i][k], a[num][k]);
			f ^= 1;
		}
		for(int j = i+1; j <= n; j++) {
			while(a[j][i]) {
				int t = a[i][i] / a[j][i];
				if(t) for(int k = i; k <= n; k++) a[i][k] = mns(a[i][k], mul(a[j][k], t));
				for(int k = i; k <= n; k++) swap(a[i][k], a[j][k]);
				f ^= 1;
			}
		}
		ans = mul(ans, a[i][i]);
	}
	return f ? mns(P, ans) : ans;
}
		

int main() {
	n = read(); P = read();
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) a[i][j] = read() % P;
	printf("%d\n", calc() % P);
	return 0;
}
