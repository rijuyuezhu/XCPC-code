/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-13 22:41:48
 * @Description: https://codeforces.com/contest/1712/problem/B
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
void work() {
   int n = read();
   if(n & 1) {
      printf("1 ");
      for(int i = 2; i <= n; i += 2) printf("%d %d ", i+1, i);
      printf("\n");
   } else {
      for(int i = 1; i <= n; i += 2) printf("%d %d ", i+1, i);
      printf("\n");
   }
}
int main() {
   int t = read();
   while(t--) work();
   return 0;
}