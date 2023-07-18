/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-02 16:09:06
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1048&pid=1003   
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
const int MAXN = 1e6 + 5;
void work() {


}
int main() {
   int T = read();
   while(T--) work();
   return 0;
}