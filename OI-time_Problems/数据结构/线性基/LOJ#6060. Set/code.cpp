#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 1e5 + 5, B = 63;
int n; 
ull a[MAXN], s, b[B];
int gb(ull x, int i) {return (x >> i) & 1;}
void ins(ull v) {
	for(int i = B-1; i >= 0; i--)
		if(!gb(s, i) && gb(v, i)) {
			if(!b[i]) {
				b[i] = v;
				return ;
			}
			v ^= b[i];
		}
	for(int i = B-1; i >= 0; i--)
		if(gb(s, i) && gb(v, i)) {
			if(!b[i]) {
				b[i] = v;
				return ;
			}
			v ^= b[i];
		}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read(), s ^= a[i];
	for(int i = 1; i <= n; i++) ins(a[i]);
	ull ans = 0;
	for(int i = B-1; i >= 0; i--) 
		if(!gb(s, i) && !gb(ans, i)) ans ^= b[i];
	for(int i = B-1; i >= 0; i--)
		if(gb(s, i) && gb(ans, i)) ans ^= b[i];
	printf("%llu\n", ans);
	return 0;
}
