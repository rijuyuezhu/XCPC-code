/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-28 16:13:23
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1047&pid=1011
 * @Tag: 
*/
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int B = 53;
const int MAXN = 1e5 + 5;

int n;
ll a[MAXN], ans;
namespace Trie {
   struct Node {
      int ch[2], tag;
   }e[MAXN * B];
   int tot;
   void clear() {
      tot = 0;
   }
   void insert(ll v) {
      int now = 1;
      for(int i = B-1; i >= 0; i--) {
         if(!e[now].ch[(v >> i) & 1]) e[e[now].ch[(v >> i) & 1] = ++tot] = (Node){{0, 0}, 0};
         now = e[now].ch[(v >> i) & 1];
      }
      e[now].tag = 1;
   }
   ll query(ll v) {
      int now = 1;
      ll ans = 0;
      for(int i = B-1; i >= 0; i--) {
         if(e[now].ch[((v >> i) & 1) ^ 1])
            now = e[now].ch[((v >> i) & 1) ^ 1], ans += 1ll << i;
         else
            now = e[now].ch[(v >> i) & 1];
      }
      return ans;
   }
}
void work() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
   ans = 0;
   Trie::clear();
   Trie::insert(0);
   for(int i = 1; i <= n; i++) {
      a[i] ^= a[i-1];
      Trie::insert(a[i]);
      ans = max(ans, Trie::query(a[i]));
   }
   printf("%lld\n", ans);
}
int main() {
   int t; scanf("%d", &t);
   while(t--) work();
   return 0;
}