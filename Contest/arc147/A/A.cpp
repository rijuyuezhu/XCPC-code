/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-09 09:03:37
 * @Description: 
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
using ll = long long;
using db = double;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
const int MAXN = 2e5 + 5;
multiset<int> st;
int n, ans;
int main() {
   n = read();
   for(int i = 1; i <= n; i++) {
      int v = read();
      st.insert(v);
   }
   while(st.size() > 1) {
      int mn = *st.begin();
      int mx = *--st.end(); st.erase(--st.end());
      if(mx % mn != 0) st.insert(mx % mn);
      ++ans;
   }
   printf("%d\n", ans);
   return 0;
}