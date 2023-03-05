// https://codeforces.com/contest/1703/problem/D

#include<cstdio>
#include<set>
#include<cstring>
using namespace std;
typedef unsigned long long ull;
const int BAS = 26;
const int MAXN = 1e5+5;
set<ull> st;
int n;
char s[MAXN][10];
int len[MAXN];
ull calc(char* str, int l) {
   ull ret = 0;
   for(int i = 0; i < l; i++)
      ret = ret * BAS + (str[i] - 'a');
   return ret;
}
void work() {
   st.clear();
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) {
      scanf("%s", s[i]); len[i] = strlen(s[i]);
      st.insert(calc(s[i], len[i]));
   }
   for(int i = 1; i <= n; i++) {
      for(int j = 0; j < len[i]; j++) {
         if(st.count(calc(s[i], j+1)) && st.count(calc(s[i]+j+1, len[i]-j-1))) {
            printf("1");
            goto END;
         }
      }
      printf("0");
      END:;
   }
   printf("\n");
}
int main() {
   //freopen("D.in", "r", stdin);
   int t; scanf("%d", &t);
   for(int i = 1; i <= t; i++) work();
   return 0;
}