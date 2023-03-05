/*
 * @Author: rijuyuezhu
 * @Date: 2022-08-16 07:23:37
 * @Description: https://codeforces.com/contest/1712/problem/E2
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
const int MAXN = 2e5 + 5;
const int MAX2N = 4e5 + 5;
const int MAXQ = 1e5 + 5;
ll gcd(ll x, ll y) {
   return !y ? x : gcd(y, x % y);
}
ll lcm(ll x, ll y) {
   return x / gcd(x, y) * y;
}
struct Qry {
   int l, r, v;
   // v < 0: id = -v
   // v >= 0 f(l, r) = v
};
bool cmp(const Qry& a, const Qry& b) {
   if(a.r != b.r) return a.r < b.r;
   return a.v > b.v;
}
vector<Qry> qry;
int t, n;
ll ans[MAXQ];
vector<int> fact[2 * MAXN];
namespace BIT {
   ll t[MAXN];
   void add(int x, ll v) {
      for(int i = x; i <= n; i += i & -i) t[i] += v;
   }
   ll sum(int x) {
      ll res = 0;
      for(int i = x; i; i -= i & -i) res += t[i];
      return res;
   }
   ll sum(int x, int y) {
      return sum(y) - sum(x-1);
   }
}
ll binom3(ll x) {
   return x * (x-1) * (x-2) / 6;
}

int main() {
   t = read();
   n = 0;
   for(int i = 1; i <= t; i++) {
      int l = read(), r = read();
      n = max(r, n);
      qry.push_back((Qry){l, r, -i});
   }
   for(int i = 1; i <= 2 * n; i++)
      for(int j = i * 3; j <= 2 * n; j += i)
         fact[j].push_back(i);
   for(int k = 1; k <= n; k++) 
      for(int ii = 0; ii < (int)fact[2 * k].size(); ii++) {
         int i = fact[2 * k][ii], ans = 0;
         ll l_1 = lcm(k, i);
         if(l_1 > 2 * k) continue;
         for(int jj = ii+1; jj < (int)fact[2 * k].size(); jj++) {
            int j = fact[2 * k][jj];
            ll l_2 = lcm(l_1, j);
            if(l_2 == k || (l_2 == 2 * k && i + j > k)) ans++;
         }
         if(ans > 0) qry.push_back((Qry){i, k, ans});
      }
   sort(qry.begin(), qry.end(), cmp);
   for(auto now : qry) {
      if(now.v < 0) {
         ans[-now.v] = binom3(now.r-now.l+1) - BIT::sum(now.l, now.r);
      } else {
         BIT::add(now.l, now.v);
      }
   }
   for(int i = 1; i <= t; i++) printf("%lld\n", ans[i]);
   return 0;
}