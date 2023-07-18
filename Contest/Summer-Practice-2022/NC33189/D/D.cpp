/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-30 12:20:23
 * @Description: https://ac.nowcoder.com/acm/contest/33189/D
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<random>
#include<vector>
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
const int MAXN = 15;
int n, q, m[MAXN];
struct Node 
int main() {
   n = read(), q = read();
   for(int i = 1; i <= n; I++) 
   return 0;
}