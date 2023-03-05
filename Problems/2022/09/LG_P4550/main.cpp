/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-04 17:06:10
 * @Description: https://www.luogu.com.cn/problem/P4550
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
using db = double;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXN = 1e4 + 5;
int n;
db a[MAXN], b[MAXN];
int main() {
   n = read();
   a[n] = b[n] = 0;
   for(int i = n-1; i >= 0; --i) {
      a[i] = (db)n / (n - i) + a[i+1];
      b[i] = 2 * (db)i / (n - i) * a[i] + (db)n / (n - i) + b[i+1] + 2 * a[i+1];
   }
   printf("%.2lf\n", (a[0] + b[0]) / 2);
   return 0;
}