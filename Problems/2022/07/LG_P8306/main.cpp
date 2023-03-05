/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 22:24:01
 * @Description: https://www.luogu.com.cn/problem/P8306
 * @Tag: Trie
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
typedef long long ll;
const int MAXL = 3e6 + 5;
int tran(char ch) {
   if(islower(ch)) return ch - 'a';
   else if(isupper(ch)) return ch - 'A' + 26;
   else return ch - '0' + 52;
}
namespace Trie {
   const int MAXNODE = 3e6 + 5;
   struct Node {
      int ch[62], siz;
   }e[MAXNODE];
   int tot;
   int crenode() {
      e[++tot] = (Node){{0}, 0};
      return tot;
   }
   void clear() {
      tot = 0; crenode();
   }
   void insert(char* s) {
      int l = strlen(s);
      int now = 1; e[now].siz++;
      for(int i = 0; i < l; i++) {
         int v = tran(s[i]);
         if(!e[now].ch[v]) e[now].ch[v] = crenode();
         now = e[now].ch[v];
         e[now].siz++;
      }
   }
   int query(char* s) {
      int l = strlen(s);
      int now = 1;
      for(int i = 0; i < l; i++) {
         int v = tran(s[i]);
         if(!e[now].ch[v]) return 0;
         now = e[now].ch[v];
      }
      return e[now].siz;
   }
}
char str[MAXL];
int n, q;
void work() {
   Trie::clear();
   scanf("%d%d", &n, &q);
   for(int i = 1; i <= n; i++) {
      scanf("%s", str);
      Trie::insert(str);
   }
   for(int i = 1; i <= q; i++) {
      scanf("%s", str);
      printf("%d\n", Trie::query(str));
   }
}
int main() {
   #ifdef LOCAL
   freopen("main.in", "r", stdin);
   #endif
   int T;
   scanf("%d", &T);
   while(T--) work();
   return 0;
}