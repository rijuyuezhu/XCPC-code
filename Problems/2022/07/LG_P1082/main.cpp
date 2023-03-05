/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-30 16:18:43
 * @Description: https://www.luogu.com.cn/problem/P1082
 * @Tag: 数论，同余，扩展欧几里得算法
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
int a, b;
void exgcd(int a, int b, int &x, int &y) {
   if(!b) x = 1, y = 0;
   else exgcd(b, a % b, y, x), y -= a / b * x;
}
int inv(int v) {
   int x, y;
   exgcd(v, b, x, y);
   return (x % b + b) % b;
}
int main() {
   a = read(), b = read();
   printf("%d\n", inv(a));
   return 0;
}