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
int n;
namespace Linearbasis {
	const int B = 51;
	ll t[B];
	void ins(ll x) {
		for(int i = B-1; i >= 0; i--)
			if((x >> i) & 1) {
				if(!t[i]) {
					t[i] = x;
					break;
				} else x ^= t[i];
			}
	}
	ll qry() {
		ll ans = 0;
		for(int i = B-1; i >= 0; i--) 
			ans = max(ans, ans ^ t[i]);
		return ans;
	}
}
using namespace Linearbasis;
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		ll k = read();
		ins(k);
	}
	printf("%lld\n", qry());
	return 0;
}
