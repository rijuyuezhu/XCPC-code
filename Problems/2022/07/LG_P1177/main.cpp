/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:24:53
 * @Description: https://www.luogu.com.cn/problem/P1177
 * @Tag: 快速排序
*/


#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<algorithm>
const int MAXN = 1e5+5;

int n, a[MAXN];
int getrand(int l, int r) {//in [l, r]
   return (1ll * rand() * RAND_MAX + rand()) % (r-l+1) + l;
}
void sort_array(int l, int r) {//sort [l, r]
   if(l >= r) return;
   int st = a[getrand(l, r)];
   int i = l, j = r;
   while(i <= j) {
      while(i <= r && a[i] < st) i++;
      while(j >= l && a[j] > st) j--;
      if(i <= j) {
         std::swap(a[i], a[j]);
         i++; j--;
      }
   }
   sort_array(i, r);
   sort_array(l, j);
}
int main() {
   srand(time(NULL));
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
   sort_array(1, n);
   for(int i = 1; i <= n; i++) printf("%d%c", a[i], i==n ? '\n' : ' ');
   return 0;
}