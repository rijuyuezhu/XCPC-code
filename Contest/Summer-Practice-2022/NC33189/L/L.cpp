/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-30 14:26:03
 * @Description: https://ac.nowcoder.com/acm/contest/33189/L
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
const double s2 = sqrt(2.0);
int n, k;
double a;
void tran(int &n, double &a) {
   if(n == 4) {
      a *= 0.3333333333333333;
   } else if(n == 6) {
      n = 8;
      a *= 0.7071067811865476;
   } else if(n == 8) {
      n = 6;
      a *= 0.47140452079103173;
   } else if(n == 12) {
      n = 20;
      a *= 1.170820393249937;
   } else if(n == 20) {
      n = 12;
      a *= 1.0786893254585272;
   }
}
void work() {
   scanf("%d%lf%d", &n, &a, &k);
   if(n == 4 || n == 6 || n == 8 || n == 12 || n == 20) {
      for(int i = 1; i <= k; i++) tran(n, a);
      printf("possible %d %lf\n", n, a);
   } else printf("impossible\n");
}
int main() {
   int T; scanf("%d", &T);
   while(T--) work();
   return 0;
}