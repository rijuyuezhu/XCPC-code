#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
using db = double;
const int MAXN = 2e5 + 5;
int n, x, a[MAXN];
void work() {
   scanf("%d%d", &n, &x);
   for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
   int ans = 0, l = -2e9, r = 2e9;
   for(int i = 1; i <= n; i++) {
      l = max(l, a[i]-x);
      r = min(r, a[i]+x);
      if(l > r) {
         l = a[i]-x;
         r = a[i]+x;
         ++ans;
      }
   }
   printf("%d\n", ans);
}
int main() {
   int t;
   scanf("%d", &t);
   while(t--) work();
}