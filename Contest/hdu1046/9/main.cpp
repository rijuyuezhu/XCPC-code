/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 13:04:39
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1046&pid=1009
 * @Tag: 堆，贪心
*/

#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN = 100005;
const int INF = 1e9+5;
int n, k, ans;
struct Line {
   int l, r;
}seg[MAXN];
bool operator < (const Line& a, const Line& b) {return a.l < b.l;}
priority_queue<int, vector<int>, greater<int> > pq;
void work() {
   scanf("%d%d", &n, &k);
   for(int i = 1; i <= n; i++) {
      scanf("%d%d", &seg[i].l, &seg[i].r);
   }
   sort(seg + 1, seg + 1 + n);
   seg[n+1].l = INF;
   ans = 0;
   pq = priority_queue<int, vector<int>, greater<int> >();
   for(int i = 1; i <= n+1; i++) {
      int nowx = seg[i].l;
      while(pq.size() && pq.top() < nowx) {
         ans++;
         for(int j = 1; j <= k; j++) {
            if(pq.size()) pq.pop();
            else break;
         }
      }
      pq.push(seg[i].r);
   }
   printf("%d\n", ans);
}
int main() {
   int t; scanf("%d", &t);
   while(t--) work();
   return 0;
}
