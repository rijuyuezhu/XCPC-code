/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-30 12:56:15
 * @Description: https://ac.nowcoder.com/acm/contest/33189/K
 * @Tag: 
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
const int pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
int n, ans;
int jump(int x) {
   for(int t = 1; t <= 8; t++) {
      int num = ((1ll - 1ll * (pow10[t]-1) * x) % n + n) % n;
      if(num < pow10[t]) return t;
   }
   return 0;
}
int main() {
   n = read();
   if(n == 1) {
      printf("0\n");
      return 0;
   }
   for(int i = 0; i < n; i++) ans += jump(i);
   printf("%d\n", ans);
   return 0;
}