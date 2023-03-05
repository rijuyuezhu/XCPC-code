#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
using db = double;
const int MAXM = 1e5 + 5;
int n, m, a[MAXM], d[MAXM];
bool cmp(int a, int b) {return a > b;}
void work() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= m; i++)
      scanf("%d", &a[i]);
   sort(a + 1, a + 1 + m);
   for(int i = 1; i <= m; i++) {
      d[i] = a[i == m ? 1 : i+1] - a[i] - 1;
      if(d[i] < 0) d[i] += n;
   }
   sort(d + 1, d + 1 + m, cmp);
   int day = 0, pro = 0;
   for(int i = 1; i <= m; i++) {
      if(d[i] - day * 2 >= 3) pro += d[i] - day * 2 - 1, day += 2;
      else if(d[i] - day * 2 >= 1) {
         pro += 1;
         break;
      }
   }
   printf("%d\n", n - pro);
}
int main() {
   int t;
   scanf("%d", &t);
   while(t--) work();
   return 0;
}