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
const int P = 1e9 + 7, t1 = 188305837, t2 = 233230706, x1 = 94153035, x2 = 905847205, x1n = 64353223, x2n = 847809841, B = 70000;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int pw1[B], pw2[B], pw1n[B], pw2n[B], ans;
namespace Mker
{
	unsigned long long SA,SB,SC;
	void init(){scanf("%llu%llu%llu",&SA,&SB,&SC);}
	unsigned long long rand()
	{
	    SA^=SA<<32,SA^=SA>>13,SA^=SA<<1;
	    unsigned long long t=SA;
		SA=SB,SB=SC,SC^=t^SA;return SC;
	}
}
int Pow1(int k) {return mul(pw1n[k >> 16], pw1[k & 65535]);}
int Pow2(int k) {return mul(pw2n[k >> 16], pw2[k & 65535]);}
int main() {
	pw1[0] = pw2[0] = pw1n[0] = pw2n[0] = 1;
	for(int i = 1; i < 65536; i++) {
		pw1[i] = mul(pw1[i-1], x1);
		pw2[i] = mul(pw2[i-1], x2);
		pw1n[i] = mul(pw1n[i-1], x1n);
		pw2n[i] = mul(pw2n[i-1], x2n);
	}
	int T = read();
	Mker::init();
	for(int i = 1; i <= T; i++) {
		int n = Mker::rand() % (P-1);
		ans ^= mul(t2, mns(Pow1(n), Pow2(n)));
	}
	printf("%d\n", ans);
	return 0;
}
