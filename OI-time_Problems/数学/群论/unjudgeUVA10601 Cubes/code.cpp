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
const int B = 6, N = 12;
ll C[13][13];
int col[7];
void init() {
	C[0][0] = 1;
	for(int i = 1; i <= 12; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			C[i][j] = C[i-1][j-1] + C[i-1][j];
		}
	}
}
ll divide(int k) {//divide col, per group size is k
	int tot = 0; ll ans = 1;
	for(int i = 1; i <= B; i++) {
		if(col[i] % k != 0) return 0;
		tot += col[i] / k;
	}
	for(int i = 1; i <= B; i++) {
		ans *= C[tot][col[i] / k];
		tot -= col[i] / k;
	}
	return ans;
}
int main() {
	init();
	for(int t = read(); t; t--) {
		for(int i = 1; i <= B; i++) col[i] = 0;
		for(int i = 1; i <= N; i++) col[read()]++;
		ll ans = 0;
		//P1
		ans += divide(1);
		//P2
		ans += 4 * 2 * divide(3);
		//P3
		ans += 3 * (2 * divide(4) + 1 * divide(2));
		//P4
		for(int i = 1; i <= B; i++) if(col[i] > 0) {
			col[i] --;
			for(int j = 1; j <= B; j++) if(col[j] > 0) {
				col[j] --;
				ans += 6 * divide(2);
				col[j] ++;
			}
			col[i] ++;
		}
		ans /= 24;
		printf("%lld\n", ans);
	}
	return 0;
}
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
const int B = 6, N = 12;
ll C[13][13];
int col[7];
void init() {
	C[0][0] = 1;
	for(int i = 1; i <= 12; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++) {
			C[i][j] = C[i-1][j-1] + C[i-1][j];
		}
	}
}
ll divide(int k) {//divide col, per group size is k
	int tot = 0; ll ans = 1;
	for(int i = 1; i <= B; i++) {
		if(col[i] % k != 0) return 0;
		tot += col[i] / k;
	}
	for(int i = 1; i <= B; i++) {
		ans *= C[tot][col[i] / k];
		tot -= col[i] / k;
	}
	return ans;
}
int main() {
	init();
	for(int t = read(); t; t--) {
		for(int i = 1; i <= B; i++) col[i] = 0;
		for(int i = 1; i <= N; i++) col[read()]++;
		ll ans = 0;
		//P1
		ans += divide(1);
		//P2
		ans += 4 * 2 * divide(3);
		//P3
		ans += 3 * (2 * divide(4) + 1 * divide(2));
		//P4
		for(int i = 1; i <= B; i++) if(col[i] > 0) {
			col[i] --;
			for(int j = 1; j <= B; j++) if(col[j] > 0) {
				col[j] --;
				ans += 6 * divide(2);
				col[j] ++;
			}
			col[i] ++;
		}
		ans /= 24;
		printf("%lld\n", ans);
	}
	return 0;
}
