/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-26 10:03:13
 * @Description: https://www.luogu.com.cn/problem/P4777
 * @Tag: 扩展中国剩余定理，
*/
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXN = 1e5 + 5;
ll mul(ll a, ll b, ll P) {
   ll c = (ldb)a / P * b;
   ll res = (ull)a * b - (ull)c * P;
   return res;
}
ll gcd(ll a, ll b) {
   return !b ? a : gcd(b, a % b);
}
ll lcm(ll a, ll b) {
   return a / gcd(a, b) * b;
}
void exgcd(ll a, ll b, ll &x, ll &y) {
   if(!b) x = 1, y = 0;
   else exgcd(b, a % b, y, x), y -= a / b * x;
}
int n;
ll b[MAXN], m[MAXN];
/**
 * x=a mod n
 * x=b mod m
 * x=pn+a=qm+b
 * pn-qm=b-a
 * x=p_0n+a mod lcm(n,m)
**/
void solve(ll a, ll n, ll b, ll m, ll &retB, ll &retM) {
   ll A = n, B = m, C = (b - a) % B + B, G = gcd(A, B);
   if(C % G) exit(1);
   ll x, y, st = B / G;
   exgcd(A, B, x, y);
   x = mul(x % st + st, C / G, st);
   retM = lcm(n, m);
   retB = (a + mul(x, n, retM)) % retM;
}
void exCRT(ll &B, ll &M) {
   B = b[1], M = m[1];
   for(int i = 2; i <= n; i++)
      solve(B, M, b[i], m[i], B, M);
}
int main() {
   n = read();
   for(int i = 1; i <= n; i++) m[i] = read(), b[i] = read();
   ll B, M;
   exCRT(B, M);
   printf("%lld\n", B);
   return 0;
}
