/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-09 09:18:56
 * @Description: 
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
using ll = long long;
using db = double;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}
constexpr int MAXN = 405;
constexpr int BUFFSIZE = 1e6 + 5;
char buff[BUFFSIZE];
int buffed, buffcnt;
int A[MAXN], n, B[MAXN], m;
vector<int> Adj[2];
void printA(int p) {
   ++buffcnt;
   buffed += sprintf(buff + buffed, "A %d\n", p);
}
void printB(int p) {
   ++buffcnt;
   buffed += sprintf(buff + buffed, "B %d\n", p);
}
int main() {
   n = read();
   for(int i = 1; i <= n; i++) {
      A[i] = read();
   }
   for(int i = 1; i <= n; i++) {
      if(i % 2 != A[i] % 2) 
         Adj[i % 2].push_back(i);
   }
   for(int i = 0; i < (int)Adj[0].size(); i++) {
      int v0 = Adj[0][i], v1 = Adj[1][i];
      while(v0 > 2) {
         swap(A[v0], A[v0 - 2]); v0 -= 2; printB(v0);
      }
      while(v1 > 1) {
         swap(A[v1], A[v1 - 2]); v1 -= 2; printB(v1);
      }
      swap(A[1], A[2]); printA(1);
   }
   m = 0;
   for(int i = 1; i <= n; i += 2) B[++m] = A[i];
   for(int i = 1; i < m; i++)
      for(int j = m; j >= i+1; j--)
         if(B[j-1] > B[j]) {
            swap(B[j-1], B[j]);
            printB(2 * j - 3);
         }
   m = 0;
   for(int i = 2; i <= n; i += 2) B[++m] = A[i];
   for(int i = 1; i < m; i++)
      for(int j = m; j >= i+1; j--)
         if(B[j-1] > B[j]) {
            swap(B[j-1], B[j]);
            printB(2 * j - 2);
         }
   buff[buffed] = '\0';
   printf("%d\n%s", buffcnt, buff);
   return 0;
}