/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:28:27
 * @Description: https://www.luogu.com.cn/problem/P3378
 * @Tag: 堆
*/

#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 1e6+5;
namespace Heap {
   int h[MAXN], tot;
   void insert(int x) {
      h[++tot] = x;
      int now = tot;
      while(now > 1 && h[now >> 1] > h[now]) {
         swap(h[now >> 1], h[now]);
         now >>= 1;
      }
   }
   int top() {
      return h[1];
   }
   void pop() {
      h[1] = h[tot--];
      int now = 1;
      while( (now << 1) <= tot) {
         int s = now << 1;
         if(s < tot && h[s+1] < h[s]) s |= 1;
         if(h[now] > h[s]) {
            swap(h[now], h[s]);
            now = s;
         } else
            return;
      }
   }
}
using Heap::top;
using Heap::pop;
using Heap::insert;
int n;
int main() {
   //freopen("main.in", "r", stdin);
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) {
      int op; scanf("%d", &op);
      if(op == 1) {
         int x; scanf("%d", &x);
         insert(x);
      } else if(op == 2) {
         printf("%d\n", top());
      } else {
         pop();
      }
   }
   return 0;
}