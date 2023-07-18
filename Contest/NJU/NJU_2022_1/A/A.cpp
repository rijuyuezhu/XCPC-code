/*
 * @Author: rijuyuezhu
 * @Date: 2022-09-08 12:58:50
 * @Description: 
 * @Tag: 
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
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
int rrev, crev, xyrev, n, m;
bool is[505][505];
void print(int x, int y) {
   int nx, ny;
   if(xyrev) {
      printf("%d %d\n", nx = crev ? m - y + 1 : y, ny = rrev ? n - x + 1 : x);
   } else {
      printf("%d %d\n", nx = rrev ? n - x + 1 : x, ny = crev ? m - y + 1 : y);
   }
   if(is[nx][ny]) {
      printf("Wrong!");
      exit(0);
   }
   is[nx][ny] = 1;
}
int main() {
   n = read(), m = read();
   if(n % 2 == 0) swap(n, m), xyrev ^= 1;
   if(m % 2 == 1) {
      if(n > m) swap(n, m), xyrev ^= 1;
   }// let n <= m
   if(m % 2 == 0) {
      for(int i = 1; i <= n-1; i++)
         print(i, 1), print(i, 2);
      if(m == 2)
         print(n, 1), print(n, 2);
      else {
         print(n, 1); print(n-1, 3); print(n, 2); print(n-1, 4);
         print(n, 3); print(n, 4);
      }
      for(int j = 3; j <= m; j += 2) {
         if(j % 4 == 3) {
            for(int i = n-2; i >= 2; i--)
               print(i, j), print(i, j+1);
            if(j == m-1)
               print(1, m-1), print(1, m);
            else {
               print(1, j); print(2, j+2); print(1, j+1); print(2, j+3);
               print(1, j+2); print(1, j+3);
            }
         } else {
            for(int i = 3; i <= n-1; i++)
               print(i, j), print(i, j+1);
            if(j == m-1)
               print(n, m-1), print(n, m);
            else {
               print(n, j); print(n-1, j+2); print(n, j+1); print(n-1, j+3);
               print(n, j+2); print(n, j+3);
            }
         }
      }
   } else {
      if(n > 3) {
         for(int i = 1; i <= n-1; i++)
            print(i, 1), print(i, 2);
         if(m != 5) {
            print(n, 1); print(n-1, 3); print(n, 2); print(n-1, 4);
            print(n, 3); print(n, 4);
         }
         for(int j = 3; j <= m - 3; j += 2) {
            if(j % 4 == 3) {
               for(int i = n-2; i >= 2; i--)
                  print(i, j), print(i, j+1);
               if(j != m - 4) {
                  print(1, j); print(2, j+2); print(1, j+1); print(2, j+3);
                  print(1, j+2); print(1, j+3);
               }
            } else {
               for(int i = 3; i <= n-1; i++)
                  print(i, j), print(i, j+1);
               if(j != m - 4) {
                  print(n, j); print(n-1, j+2); print(n, j+1); print(n-1, j+3);
                  print(n, j+2); print(n, j+3);
               }
            }
         }
         if(m % 4 == 3) {
            print(1, m-4); print(2, m-2); print(1, m-3); print(2, m-1); print(1, m-2); print(2, m); print(1, m-1); print(1, m);
            for(int i = 3; i <= n-3; i += 2) {
               print(i+1, m-2); print(i+1, m-1); print(i, m-2); print(i+1, m); print(i, m-1); print(i, m);
            }
            print(n, m-1); print(n, m); print(n-1, m-2); print(n, m-2); print(n-2, m-1); print(n-2, m-2); print(n-1, m); print(n-2, m); print(n-1, m-1);
         } else {
            rrev ^= 1;
            print(1, m-4); print(2, m-2); print(1, m-3); print(2, m-1); print(1, m-2); print(2, m); print(1, m-1); print(1, m);
            for(int i = 3; i <= n-3; i += 2) {
               print(i+1, m-2); print(i+1, m-1); print(i, m-2); print(i+1, m); print(i, m-1); print(i, m);
            }
            print(n, m-1); print(n, m); print(n-1, m-2); print(n, m-2); print(n-2, m-1); print(n-2, m-2); print(n-1, m); print(n-2, m); print(n-1, m-1);
         }
      } else {//n == 3
         for(int i = 1; i <= m-3; i += 2) {
            print(1, i); print(2, i); print(1, i+1); print(3, i); print(2, i+1); print(3, i+1);
         }
         print(2, m); print(3, m); print(1, m-1); print(1, m); print(2, m-2); print(1, m-2); print(3, m-1); print(3, m-2); print(2, m-1);
      }
   }
   return 0;
}