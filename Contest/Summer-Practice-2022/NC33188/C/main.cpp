// https://ac.nowcoder.com/acm/contest/33188/C

#include<cstdio>
#include<cstring>
const int MAXN = 2e6 + 5;
const int MAXLEN = 2e7 + 5;

int n;
char s[MAXLEN];
struct Node {
   int ch[5], fl;
}t[MAXLEN];

void add(char* s) {
   int now = 1;
   int len = strlen(s);
   for(int i = 0; i < len; i++) {
      now = t[now].ch[s[i] - '0'];
   }
   t[now].fl++;
}
void dfs(int u, int stp) {
   s[stp] = 0;
   for(int i = 1; i <= t[u].fl; i++) printf("%s", s);
   for(int i = 0; i < 5; i++) 
      if(t[u].ch[i]) {
         s[stp] = i + '0';
         dfs(t[u].ch[i], stp+1);
      }
}
int main() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i++) {
      scanf("%s", s);
      add(s);
   }
   dfs(1, 0);
   return 0;
}