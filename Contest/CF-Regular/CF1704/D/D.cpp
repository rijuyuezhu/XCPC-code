#include <algorithm>
#include <iostream>
using namespace std;
using ll = long long;
using db = double;
const int MAXN = 1e5 + 5;
int n, m;
ll val[MAXN];

void work() {
   cin >> n >> m;
   for(int i = 1; i <= n; i++) {
      val[i] = 0;
      for(int j = 1; j <= m; j++) {
         int v; cin >> v;
         val[i] += 1ll * j * v;
      }
   }
   if(val[1] == val[2]) {
      for(int i = 3; i <= n; i++)
         if(val[i] != val[1]) {
            cout << i << ' ' << val[i] - val[1] << endl;
            return ;
         }
   } else {
      if(val[1] == val[3])
         cout << 2 << ' ' << val[2] - val[1] << endl;
      else
         cout << 1 << ' ' << val[1] - val[2] << endl;
   }
}
int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   cout.tie(nullptr);
   int t;
   cin >> t;
   while(t--)  
      work();
   return 0;
}