#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
using db = double;
const int MAXN = 55;
int n, m;
char a[MAXN], b[MAXN];
bool work() {
   scanf("%d%d", &n, &m);
   scanf("%s%s", a+1, b+n-m+1);
   for(int i = n-m+2; i <= n; i++)
      if(a[i] != b[i])
         return 0;
   for(int i = 1; i <= n-m+1; i++)
      if(a[i] == b[n-m+1])
         return 1;
   return 0;
}
int main() {
   int t; scanf("%d", &t);
   while(t--) 
      if(work()) printf("YES\n");
      else printf("NO\n");
   return 0;
}