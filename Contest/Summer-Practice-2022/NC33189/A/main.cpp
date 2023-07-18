/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-30 15:41:00
 * @Description: https://ac.nowcoder.com/acm/contest/33189/A
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
const int MAXN =  1e5 + 5;
int w[MAXN], q[MAXN], id[MAXN], n, m;

int main() {
   n = read(), m = read();
   for(int i = 1; i <= n; i++) w[i] = read();
}