/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-04 12:56:07
 * @Description: http://acm.hdu.edu.cn/contest/problem?cid=1049&pid=1012
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
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
const int MAXN = 3e5 + 5;
int a[MAXN], d[MAXN], n, k;
int stk[MAXN], _stk;
vector<int> lst, ad, ans;
bool cmp(int a, int b) {return a > b;}
void work() {
   n = read(), k = read();
   for(int i = 1; i <= n; i++) a[i] = read(), d[i] = 0;
   _stk = 0;
   lst.clear(); ad.clear(); ans.clear();
   for(int i = 1; i <= n; i++) {
      while(_stk >= 1 && a[stk[_stk]] < a[i]) {
         if(k) {
            --k;
            d[stk[_stk]] = 1;
            --_stk;
         } else break;
      }
      stk[++_stk] = i;
      if(k == 0 || i == n) {
         for(int j = 1; j <= _stk; j++) lst.push_back(a[stk[j]]);
         for(int j = i+1; j <= n; j++) lst.push_back(a[j]);
         break;
      }
   }
   for(int i = 1; i <= n; i++) if(d[i]) ad.push_back(a[i]);
   sort(ad.begin(), ad.end(), cmp);
   int p = 0, q = 0;
   while(p < (int)lst.size() && q < (int)ad.size()) {
      if(lst[p] >= ad[q]) ans.push_back(lst[p++]);
      else ans.push_back(ad[q++]);
   }
   while(p < (int)lst.size()) ans.push_back(lst[p++]);
   while(q < (int)ad.size()) ans.push_back(ad[q++]);
   for(int i = 0; i < (int)ans.size(); i++) printf("%d%c", ans[i], (i == (int)ans.size()-1) ? '\n' : ' ');
}
int main() {
   int T = read();
   while(T--) work();
   return 0;
}