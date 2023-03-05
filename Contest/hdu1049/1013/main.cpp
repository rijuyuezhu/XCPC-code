/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-04 15:40:32
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1049&pid=1007
 * @Tag: 
*/
#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
typedef long long ll;
char In[1000000], *ptrs = In, *ptrt = In;
#define getchar() (ptrs == ptrt && (ptrt = (ptrs = In) + fread(In, 1, 1000000, stdin), ptrs == ptrt) ? EOF : *ptrs++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
int P, a, n, q;
int qpow(int a, int n=P-2) {int ret = 1; for(; n; n >>= 1, a = 1ll * a * a % P) if(n & 1) ret = 1ll * ret * a % P; return ret;}
map<int, int> mp;
int BSGS(int a, int b) {
   int B = 0;
   mp.clear();
	while(1ll * B * B <= P) B++;
	int t = qpow(a), pro = 1;
	for(int i = 0; i < B; i++) {
		if(!mp.count(1ll * pro * b % P)) mp[1ll * pro * b % P] = i;
		pro = 1ll * pro * t % P;
	}
	t = qpow(a, B); pro = 1;
	for(int i = 0; i < B; i++) {
		if(mp.count(pro)) {
			return i * B + mp[pro];
         return ;
		}
		pro = 1ll * pro * t % P;
	}
}
void work() {
   P = read(), a = read(), n = read(), q = read();
}
int main() {
   int T = read();
   while(T--) work();
	return 0;
}