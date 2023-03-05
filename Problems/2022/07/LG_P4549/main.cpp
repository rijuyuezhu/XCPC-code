/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 21:44:41
 * @Description: https://www.luogu.com.cn/problem/P4549
 * @Tag: 数论，裴蜀定理
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXN = 25;
int a[MAXN], n, ans;
int gcd(int a, int b) {
   if(!b) return a;
   else return gcd(b, a % b);
}
int main() {
   n = read();
   for(int i = 1; i <= n; i++) a[i] = read();
   ans = abs(a[1]);
   for(int i = 2; i <= n; i++) ans = gcd(ans, abs(a[i]));
   printf("%d\n", ans);
   return 0;
}