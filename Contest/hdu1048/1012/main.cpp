/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-02 13:41:58
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1048&pid=1012
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
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
const int MAXN = 2e5 + 5;
typedef pair<ll, int> pr;
typedef priority_queue<pr, vector<pr>, greater<pr> > my_pq;
int n, m, len[MAXN];
ll tim[MAXN];
struct Node {int a, s;}a[MAXN];
bool cmp(Node x, Node y) {return x.a < y.a;}
void work() {
   n = read(), m = read();
   for(int i = 1; i <= n; i++) {
      a[i].a = read(), a[i].s = read();
   }
   sort(a + 1, a + 1 + n, cmp);
   my_pq peo, que;
   for(int i = 1; i <= m; i++) que.push(pr(0, i));
   for(int i = 1; i <= m; i++) len[i] = tim[i] = 0;
   for(int i = 1; i <= n; i++) {
      while(peo.size() && peo.top().first <= a[i].a) {
         int t = peo.top().second; peo.pop();
         len[t]--; que.push(pr(len[t], t));
      }
      pr t;
      do {
         t = que.top(); que.pop();
      } while(t.first != len[t.second]);
      len[t.second]++; t.first++;
      que.push(t);
      peo.push(pr(tim[t.second] = max<ll>(tim[t.second], a[i].a) + a[i].s, t.second));
   }
   ll ans = 0;
   for(int i = 1; i <= m; i++) ans = max(ans, tim[i]);
   printf("%lld\n", ans);
}  
int main() {
   int T = read();
   while(T--) work();
   return 0;
}