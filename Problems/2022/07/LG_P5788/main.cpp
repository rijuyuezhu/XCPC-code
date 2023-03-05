/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 22:17:54
 * @Description: https://www.luogu.com.cn/problem/P5788
 * @Tag: 数据结构，单调栈
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
const int MAXN = 3e6 + 5;
int n, a[MAXN], st[MAXN], _st, f[MAXN];

int main() {
   n = read();
   for(int i = 1; i <= n; i++) a[i] = read();
   for(int i = n; i >= 1; i--) {
      while(_st && a[i] >= a[st[_st]]) --_st;
      if(!_st) f[i] = 0;
      else f[i] = st[_st];
      st[++_st] = i;
   }
   for(int i = 1; i <= n; i++) printf("%d ", f[i]);
   printf("\n");
   return 0;
}